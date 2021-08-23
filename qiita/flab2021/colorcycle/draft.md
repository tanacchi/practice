この記事は[古川研究室 AdventCalendar](https://qiita.com/flab5420/items/fc94dadc49635f0e5c9f) 4日目の記事です。
本記事は古川研究室の学生が学習の一環として書いたものです。
内容が曖昧であったり表現が多少異なったりする場合があります。

# まえがき
matplotlib で描画関数を呼び出す度に
色をグラデーションで変えたいと思ったことはありますでしょうか．
私にはあります．

今回はその方法について書かせていただこうと思います．
何番煎じかわかりませんが，
様々な記事を参考にさせていただき
個人的に落ち着く方法までたどり着いたので投稿しようと思った次第です．

この記事を読んでくれた方には
ぜひ[参考文献](#参考文献)にある記事とも比較して
どの方法を採用するかを決めていただけたらと思っております．
また，本記事には個人的な好みが散りばめられていることをご了承ください。

お急ぎの方は[実装例](#実装例)までジャンプしてもらって OK です．

# matplotlib

matplotlib は言わずと知れた Python の描画ライブラリです．
静的なグラフはもちろん，アニメーションやマウス操作などによるインタラクションなども
包括的にサポートしています．

matplotlib の機能として，
`plot` や `scatter` などの描画関数を複数回呼び出す時，
呼び出す度にグラフの色を変えてくれるというものがあります．
デフォルトでは 青→オレンジ→緑→・・・のように変化します．
本記事のゴールは，これをグラデーション状に変えることです．

# デフォルトの配色はどうなっているのか

デフォルトの配色はどうなっているかという話は，
下のページに詳しく書かれています．

https://matplotlib.org/stable/users/dflt_style_changes.html

![newcolors.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/4ecd1d88-4ab4-2796-1b9a-b216076366f7.png)
（公式サイトより抜粋）

描画関数を複数回呼び出すと， その配色がデフォルトでは`#1f77b4`（青）→`#ff7f0e`（オレンジ）→`#2ca02c`（緑）→...のように変化します（上図の上から順に）．
これらの色には 'cyan' など特別な名前が付いているわけではありません．
この配色や順番は，視認性の観点から非常によく練られています．

デフォルトの配色も非常に良いのですが，
「どういう順番になっているか」という情報が欲しいときには不便です．
描画結果のみから，どういう順番になっているかを読み取るには
色の順番を把握する必要があります．
慣れていれば色の順番はわかってくるものですが，
わかっていたとしても描画回数が多くなると
ごちゃごちゃして視認性が悪くなってしまいます．

例えば，sin(x) + 0.1*i　を描画するとこのようになる。


そこで，描画する度にグラデーション状に配色を変えたいというモチベーションが湧きます．

# どこをイジればよいか

描画関数を呼び出すたびに色を指定する
`rcParams` の `'axes.prop_cycle'` が
rcParam で指定するもの良いですが、
プログラム全体に影響が及ぶので
個人的には Axes オブジェクトごとに指定する方を好みます。
https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.set_prop_cycle.html

## `matplotlib.cm`
`cm` は **C**olor**M**ap の略です．
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
```
![sin.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/070fda73-526f-8c3d-052c-a66e99e52aa4.png)


# おまけ：2次元のグラデーション

```Python
```
![star.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/199099/236b875b-72e1-f111-0c30-8f80e6991340.png)


# おわりに

私が本記事にある内容を調べようと思った理由は，
研究で「マルチ多様体モデリングによるメタ学習」を扱う際に，
学習結果を描画する際に"タスクごとに"プロットする色をグラデーション状に変えたいとなったからです．

「マルチ多様体モデリングによるメタ学習」とは何ぞやと興味を持っていただいた方は
是非以下のリンクをご参照ください（宣伝）．

http://www.brain.kyutech.ac.jp/~furukawa/myresearch.html

# 参考文献
## 先駆者様
- https://qiita.com/skotaro/items/5c9893d186ccd31f459d
- https://qiita.com/hokekiyoo/items/cea310b2c36a01b970a6
- https://qiita.com/ShoheiKojima/items/6705ce31d6cffb64daff
- https://qiita.com/okd46/items/5940b317cd4ef5dd2dd8

## 公式ドキュメントなど

