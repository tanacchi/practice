この記事は[九工大古川研 Advent Calendar 2020](https://qiita.com/advent-calendar/2020/flab) 15日目の記事です．
本記事は古川研究室の学生が学習の一環として書いたものです．
内容が曖昧であったり表現が多少異なったりする場合があります．

# はじめに

研究室でよく使用・考察されている UKR (Unsupervised Kernel Regression) を
Pytorch という機械学習フレームワークを駆使して
ニューラルネットワーク風に組めないかという試みです．

# UKR とは

UKR とは Unsupervised Kernel Regeression の略で，
教師なし学習アルゴリズムの1種です．

## 問題設定

入力（観測変数）を
 $\{x_i\}_{i=1}^{n}$ として，
それを生成する元となった潜在空間中の変数（潜在変数） $Z = {z_i}_{i=1}^{n}$ と
潜在空間から観測空間への（滑らかな）写像 $f$ を

```math 
x_i \simeq f(z_i;Z)
```

となるように推定します．

## 目的関数

$x_i \simeq f(z_i;Z)$ となるような $f$ と $Z$ を
具体的にどう推定するのかという話に移ります．

UKR のアルゴリズムでは，以下のように目的関数を定義します．

```math
E(Z) = \frac{1}{N} \sum_i^n \| x_i - f(z_i;Z) \|^2 + \lambda \sum_i^n \| z_i \|^2
```

これを小さくするように $Z$ を推定します．

第一項は「$i$ 番目の観測データの生成元となった潜在変数 $z_i$ を
写像 $f$ によって観測空間に写像した推定点 $f(z_i)$ 」と
「実際に観測されたデータ $x_i$」の二乗誤差です．
これが，$x_i \simeq (fz_i;Z)$ となるように学習を進める働きを持ちます．

第二項は $z_i$ の L2 ノルムで，
$Z$ が無限に発散していくのを抑える働きを持ちます．

（ここでは直感的な説明をしていますが，MAP 推定の観点からも理にかなっている目的関数です．）


ここで，写像 $f$ は以下の式で表現されるものとします．

$$f(z_i) = \sum_j \frac{k(z_i, z_j) x_i}{K(z)}$$

ただし，

```math 
\begin{align}
K(z) &= \sum_{j^\prime} k(z, z_{j^\prime}) \\
k(z, \zeta) &= \exp(- \frac{1}{2 \sigma^2} \| z - \zeta \|^2)
\end{align}
```


また，UKR においては（$f$ の定義からもわかる通り），
写像 $f$ が潜在変数 $Z$ によって一意に決まるため
実質的には $Z$ の推定のみを行うことになります．
$Z$ は勾配法で推定します．

# 実装

## UKR-Layer

PyTorch で言うカスタムレイヤーで UKR を実装します．
このレイヤーの入力は観測データ $X = {x_i}_i^n$ で，
出力は $X$ の推定点 $Y = {f(z_i)}_i^n$ です．
内部に潜在変数 $Z = {z_i}_i^n$ をパラメータとして保持します．

```Python
```

## UKR-Net

UKR-Layer をただ一つ持つニューラルネットワークを構築します．
これに関しては[公式のチュートリアル](https://pytorch.org/tutorials/recipes/recipes/defining_a_neural_network.html) にもあるような話ですので割愛します．

```Python
```


## データセットの用意

主題とちょっと逸れるので読み飛ばしてもらっても大丈夫です．

[双曲放物面状](https://ja.wikipedia.org/wiki/%E6%94%BE%E7%89%A9%E9%9D%A2)のデータ分布を生成する
`gen_saddle_shape` 関数を生成します．

式で書き表すと以下のようになります．

```math
f(z_1, z_2) = \begin{pmatrix}
z_1 \\
z_2 \\
z_1^2 - z_2^2
\end{pmatrix}
```

![tmp.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/fd036615-98ed-b46d-5a6f-c3ff300eb3c3.gif)

## 学習スクリプト

そして学習時に回すスクリプトです．
これもいわゆる PyTorch の基本形以上のことはしていません．
変わっていることといえば
学習と描画を分けるために結果を `pickle` で保存していることくらいです．

```Python
```

## 描画スクリプト
学習スクリプトで保存した学習結果を描画するスクリプトです．

```Python
```

# 結果

![learning_history.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/a90ed908-826c-3a02-ec92-a650b91f68d2.png)


![sample100.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/289ca4f0-ec45-29eb-7138-b117123a1db4.gif)


# おわりに

本当は多層化してみた〜みたいなことがしたかったのですが，
アドカレに間に合わせるには時間が足りなかったです．

これが何かに応用できる日が来たら良いなあと思っています．
