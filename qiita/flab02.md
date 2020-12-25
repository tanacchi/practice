この記事は[九工大古川研 Advent Calendar 2020](https://qiita.com/advent-calendar/2020/flab) 15日目の記事です．
本記事は古川研究室の学生が学習の一環として書いたものです．
内容が曖昧であったり表現が多少異なったりする場合があります．

# はじめに

研究室でよく使用・考察されている UKR (Unsupervised Kernel Regression) を
Pytorch という機械学習フレームワークを駆使して
ニューラルネットワーク風に組めないかという試みです．

# UKR とは

UKR とは Unsupervised Kernel Regeression の略で，
その名の通り，教師なしのカーネル回帰アルゴリズムです．
観測されたデータに対して多様体でフィッティングし，
データの低次元表現を獲得します．

以下で軽く UKR の概要を説明します．
（物足りない感があるかもしれませんが，
本記事は UKR 自体の説明よりも
実装に重きを置いてますので悪しからず…．）

## 問題設定

入力（観測変数）を
$(\boldsymbol{x}_i) \in \mathbb{X}$ として，
それを生成する元となった潜在空間中の変数（潜在変数） $(\boldsymbol{z}_i) \in \mathbb{Z}$ と
潜在空間から観測空間への（滑らかな）写像 $f$ を

```math 
\boldsymbol{x}_i \simeq f(\boldsymbol{z}_i;\boldsymbol{Z})
```

となるように推定します．

## 目的関数

$\boldsymbol{x}_i \simeq f(\boldsymbol{z}_i;\boldsymbol{Z})$ となるような $f$ と $\boldsymbol{Z}$ を
具体的にどう推定するのかという話に移ります．

UKR のアルゴリズムでは，以下のように目的関数を定義します．

```math
E(\boldsymbol{Z}) = \frac{1}{N} \sum_i^n \| \boldsymbol{x}_i - f(\boldsymbol{z}_i;\boldsymbol{Z}) \|^2 + \lambda \sum_i^n \| \boldsymbol{z}_i \|^2
```

これを小さくするように $\boldsymbol{Z}$ を推定します．

第一項は「$i$ 番目の観測データの生成元となった潜在変数 $\boldsymbol{z}_i$ を
写像 $f$ によって観測空間に写像した推定点 $f(\boldsymbol{z}_i)$ 」と
「実際に観測されたデータ $\boldsymbol{x}_i$」の二乗誤差です．
これが，$\boldsymbol{x}_i \simeq f(\boldsymbol{z}_i;\boldsymbol{Z})$ となるように学習を進める働きを持ちます．

第二項は $\boldsymbol{z}_i$ の L2 ノルムで，
$\boldsymbol{Z}$ が無限に発散していくのを抑える働きを持ちます．
$\lambda$ はその制約の強さを制御するハイパーパラメータです．

（ここでは直感的な説明をしていますが，
MAP 推定の観点からも理にかなっている目的関数です．
この辺りのお話は後日公開される
@ae14watanabe さんの記事で勉強させてもらいました．）

ここで，写像 $f$ は以下の式で表現されるものとします．

$$f(\boldsymbol{z}_i) = \sum_j \frac{k(\boldsymbol{z}_i, \boldsymbol{z}_j) \boldsymbol{x}_i}{K(\boldsymbol{z})}$$

ただし，

```math 
\begin{align}
K(\boldsymbol{z}) &= \sum_{j^\prime} k(\boldsymbol{z}, \boldsymbol{z}_{j^\prime}) \\
k(\boldsymbol{z}, \boldsymbol{\zeta}) &= \exp(- \frac{1}{2 \sigma^2} \| \boldsymbol{z} - \boldsymbol{\zeta} \|^2)
\end{align}
```


また，UKR においては（$f$ の定義からもわかる通り），
写像 $f$ が潜在変数 $\boldsymbol{Z}$ によって一意に決まるため
実質的には $\boldsymbol{Z}$ の推定のみを行うことになります．
$\boldsymbol{Z}$ は勾配法で推定します．

# 実装
…の一部を以下で紹介します．
実装の全貌は Gist で公開しています．

## UKR-Layer

PyTorch で言うカスタムレイヤーで UKR を実装します．
このレイヤーの入力は観測データ $\boldsymbol{X} = {\boldsymbol{x}_i}\_i^n$ で，
出力は $\boldsymbol{X}$ の推定点 $\boldsymbol{Y} = {f(\boldsymbol{z}_i)}_i^n$ です．
内部に潜在変数 $ \boldsymbol{Z} = {\boldsymbol{z}_i}_i^n $ をパラメータとして保持します．

```Python
class UKRLayer(nn.Module):
    def __init__(self, data_num, latent_dim, sigma=1, random_seed=0):
        super().__init__()
        self.kernel = lambda Z1, Z2: torch.exp(-torch.cdist(Z1, Z2)**2 /
                                               (2 * sigma**2))
        torch.manual_seed(random_seed)
        self.Z = nn.Parameter(torch.randn(data_num, latent_dim) / 10.)

    def forward(self, X):
        kernels = self.kernel(self.Z, self.Z)
        R = kernels / torch.sum(kernels, axis=1, keepdims=True)
        Y = R @ X
        return Y
```

## UKR-Net

UKR-Layer をただ一つ持つニューラルネットワークを構築します．
これに関しては[公式のチュートリアル](https://pytorch.org/tutorials/recipes/recipes/defining_a_neural_network.html) にもあるような話ですので割愛します．

```Python
class UKRNet(nn.Module):
    def __init__(self, N, latent_dim=2, sigma=2):
        super(UKRNet, self).__init__()
        self.layer = UKRLayer(N, latent_dim, sigma)

    def forward(self, x):
        return self.layer(x)
```


## データセットの用意

主題とちょっと逸れるので読み飛ばしてもらっても大丈夫です．

[双曲放物面状](https://ja.wikipedia.org/wiki/%E6%94%BE%E7%89%A9%E9%9D%A2)のデータ分布を生成する
`gen_saddle_shape` 関数を生成します．

式で書き表すと以下のようになります．

```math
f(\boldsymbol{z}_1, \boldsymbol{z}_2) = \begin{pmatrix}
\boldsymbol{z}_1 \\
\boldsymbol{z}_2 \\
\boldsymbol{z}_1^2 - \boldsymbol{z}_2^2
\end{pmatrix}
```

![tmp.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/fd036615-98ed-b46d-5a6f-c3ff300eb3c3.gif)

## 学習スクリプト

そして学習時に回すスクリプトです．
これもいわゆる PyTorch の基本形以上のことはしていません．
変わっていることといえば
学習と描画を分けるために結果を `pickle` で保存していることくらいです．

また，目的関数の $\lambda$ （潜在変数のスケールに対する制約の強さ）は
`optimizer` の `weight_decay` で設定できます

```Python
# プロセッサの設定
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# データの準備
X = torch.from_numpy(gen_saddle_shape(N := 100).astype(np.float32)).to(device)
X_train = X.repeat(samples := 1000, 1, 1)
train = torch.utils.data.TensorDataset(X_train, X_train)
trainloader = torch.utils.data.DataLoader(train, batch_size=1, shuffle=True)

# モデル，学習の設定
model = UKRNet(N).to(device)
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(),
                      lr=0.01,
                      momentum=0.9,
                      weight_decay=1e-4)

# 学習結果，loss 保存用の変数
num_epoch = 200
Z_history = np.zeros((num_epoch, N, 2))
losses = []

# 学習ループ
with tqdm(range(num_epoch)) as pbar:
    for epoch in pbar:
        running_loss = 0.0
        for i, data in enumerate(trainloader):
            inputs, targets = data
            inputs, targets = Variable(inputs), Variable(targets)

            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, targets)
            loss.backward()
            optimizer.step()
            running_loss += loss.item()

        # 潜在変数の保存
        Z_history[epoch] = model.layer.Z.detach().cpu().numpy()
        # loss の値の保存
        losses.append(running_loss)
        # プログレスバーの表示
        pbar.set_postfix(
            OrderedDict(epoch=f"{epoch + 1}", loss=f"{running_loss:.3f}"))

# Loss の推移の描画
plt.plot(np.arange(num_epoch), np.array(losses))
plt.xlabel("epoch")
plt.show()

# 学習結果を *.pickle で保存
with open("./X.pickle", 'wb') as f:
    pickle.dump(X.detach().cpu().numpy(), f)
with open("./Z_history.pickle", 'wb') as f:
    pickle.dump(Z_history, f)
```

# 結果

epoch ごとの目的関数の値の推移をプロットしました．

![learning_history.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/11372baf-f82b-3158-7132-17b7e32367d2.png)


いい感じに学習できてそうですね．

次に，実際にデータに対して多様体でフィッティングできているかを
描画して確認します．

![sample100.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/289ca4f0-ec45-29eb-7138-b117123a1db4.gif)

# 所感

PyTorch の力を借りているので
numpy でフルスクラッチ実装するときと比べて

- 目的関数や勾配法のアルゴリズムを変えるなどのアレンジがしやすい
- GPU の力を容易に借りられる

などの点が良いなと思いました．

# おわりに

本当は多層化してみた〜みたいなことがしたかったのですが，
アドカレに間に合わせるには時間が足りなかったです．

これが何かに応用できる日が来たら良いなあと思っています．
とりあえず勾配法のアルゴリズムをいろいろ変えて遊んでみるとします．
