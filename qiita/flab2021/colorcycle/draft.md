この記事は古川研究室 Advent_calendar 4日目の記事です。
本記事は古川研究室の学生が学習の一環として書いたものです。
内容が曖昧であったり表現が多少異なったりする場合があります。

# まえがき
matplotlib で描画関数を呼び出す度に
色をグラデーションで変えたいと思ったことはありますでしょうか．
私にはあります．

今回はその方法について書かせていただこうと思います．
何番煎じかわかりませんが，
様々な記事を参考にさせていただき
個人的に落ち着く方法までたどり着いたので共有させていただこうと思った次第です．

この記事を読んでくれた方には
ぜひ参考文献にある記事とも比較して
どの方法を採用するかを決めていただけたらと思っております．
本記事には個人的な好みが散りばめられていることをご了承ください。

お急ぎの方は[実装例](#実装例)までジャンプしてもらって OK です．

# matplotlib

matplotlib は言わずと知れた Python の描画ライブラリです．
静的なグラフはもちろん，アニメーションやマウス操作などによるインタラクションなども
包括的にサポートしています．

matplotlib の機能として，
`plot` や `scatter` などの描画関数を複数回呼び出す時，
呼び出す度にグラフの色を変えてくれるというものがあります．


# デフォルトの配色はどうなっているのか

デフォルトの配色はどうなっているかというと

このように（複雑な）カラーコード指定になっている理由としては、

どういう順番になっているかという情報が欲しいときは不便。
この配色がどういう順番なのかを知っている必要がある。
慣れていれば配色の順番はわかってくるものですが、
知っていたとしても描画回数が多くなると
ごちゃごちゃして視認性が悪くなる。


例えば，sin(x) + 0.1*i　を描画するとこのようになる。


そこで，描画するごとにグラデーション状に配色を変えたいというモチベーションが湧くわけです．

# どこをイジればよいか

描画関数を呼び出すたびに色を指定する
`rcParams` の `'axes.prop_cycle'` が
rcParam で指定するもの良いですが、
プログラム全体に影響が及ぶので
個人的には Axes オブジェクトごとに指定する方を好みます。
https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.set_prop_cycle.html

## `matplotlib.cm`
`cm` は **C**olor**M**ap の略でしょうか．
割と他の記事ですと
描画関数を呼び出す度に color 引数とループのインデックスで色指定するのが多い印象．

## `cycler`

https://matplotlib.org/cycler/

matplotlib 以外にも活用できそうですね．

>Iterating over a Cycler results in the finite list of entries, to get an infinite cycle, call the Cycler object (a-la a generator)（[Cycler のドキュメントより](https://matplotlib.org/cycler/)）

とありますので，これによって配色がループするようになっているみたいですね．

さて，ではこの配色の cycler をどうやってイジるのかという話になります．
公式ドキュメントには，以下のようにグローバルな設定の仕方が紹介されていました．

```Python
from cycler import cycler
mpl.rcParams['axes.prop_cycle'] = cycler(color='bgrcmyk')
```

私の使用用途としては，プログラム全体に影響を及ぼすことは避けたいため，
https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.set_prop_cycle.html
にもありますように，`matplotlib.axes.Axes.set_prop_cycle` を用いて，
`Axes` オブジェクトごとに配色を設定したと思います．

# 実装例

```Python
import numpy as np
import matplotlib as mpl
from matplotlib import pyplot as plt


if __name__ == '__main__':
    # Making multiple sine curves.
    num_tasks = 30
    num_samples = 1000
    x = np.linspace(-np.pi, np.pi, num_samples)
    Y = np.empty((num_tasks, num_samples))
    for i in range(num_tasks):
        Y[i] = np.sin(x) + 0.1*i

    # Making list of colors.
    colors = [
        mpl.cm.cool(i) for i in np.linspace(0, 1, num_tasks, endpoint=False)
    ]

    # Drawing sine curvies.
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_prop_cycle(color=colors)  # Setting color cycle !
    for y in Y:
        ax.plot(x, y)  # Just calling plot without color option...
    plt.show()
```


# おまけ：2次元のグラデーション


# おわりに

私が本記事にある内容を調べようと思った理由は，
研究で「マルチ多様体モデリングによるメタ学習」を扱う際に，
学習結果を描画する際に"タスクごとに"プロットする色をグラデーション状に変えたいとなったからです．

「マルチ多様体モデリングによるメタ学習」とは何ぞやと興味を持っていただいた方は
是非以下のリンクをご参照ください（宣伝）．

http://www.brain.kyutech.ac.jp/~furukawa/myresearch.html

# 参考文献

-

