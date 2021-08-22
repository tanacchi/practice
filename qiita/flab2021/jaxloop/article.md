この記事は古川研究室 Advent_calendar 4日目の記事です。
本記事は古川研究室の学生が学習の一環として書いたものです。
内容が曖昧であったり表現が多少異なったりする場合があります。

---

Jax を使って学習過程を保存しつつ，Jax を使ってアルゴリズムを高速化する試みです．

# まえがき

昨年，ラボ先輩の @kpasso1015 さんがこのような記事を書かれました．

https://qiita.com/kpasso1015/items/d4ad62cc541ba4e126c7

ここで紹介されている Jax なるライブラリが非常に使いやすい上に高機能で，
今では私の研究生活においてなくてはならない存在となりました．

学習に 12 時間とかかかってツラミ．

今回はそんな問題を解決すべく，

# Jax とは

Google で開発されている Python の計算ライブラリ
Numpy と互換がありながら，自動微分が実装されている．
さらには GPU を活用した高速化が可能なライブラリ．

Jax XLA Autograd

GPU TPU なんでもこいこい．

実行時コンパイル

自動微分



# UKR とは

# 調理開始

## もととなるコード

## `jax.jit`
関数にぶち込んでも良いそう．
jit するには色々条件があるそう


## `jax.lax.scan`

他にも jax.lax.fori_loop や jax.lax.while_loop などある．

fori_loop を使うと index_update を使わざるを得ない．
<!--

ご質問ありがとうございます。

私たちのスローガンは、"できる限り常にスキャンを！"です。

これは今回の例には当てはまりませんが、一般的には、scanとfori_loopを区別するものを可能な限り使用することが良いとされています。ループキャリーを使わずにスキャンオーバーの入出力を使うと、JAXはより効率的な微分コードを生成することができます。その理由は非常に簡単で、前方パスの各ループの反復からデータを保存して、後方パスで消費する必要があるからです。そのデータがループキャリーの中にある場合、基本的にはループキャリー全体を反復ごとにスナップショットしなければなりませんが、データがスキャンされた入力と出力の中にある場合は、反復ごとに特定のスライスを保存するだけでよいことがわかっています。

このコメントは、今回のscan_funの例には当てはまりません。yをスキャンされた入力として扱うのではなく、手動でスライスを行っていますが、yのようなクローズドオーバーの値は、オートディフ目的のループキャリーの値とは扱いが異なりますので、可能な限り効率的であると考えています。

なぜなら、ループの繰り返し回数はリテラルや配列の形状だけではなく、ランタイムの値の関数でもあるからです。代表的な例としては、固定小数点の反復処理やリジェクトサンプラーなどがあり、データに依存したしきい値に達するまで反復処理を行いたい場合には、while_loopを使わざるを得ません。

(実際には、可能であればボンネット内のスキャンという観点から fori_loop を実装したいと思っていますが、覚えていないつまらない理由で現在は有効になっていません)。

 -->
carry は

> Finally, the loop-carried value carry must hold a fixed shape and dtype across all iterations



## 調理後のコード

# 結果

速度を比較

実験結果も比較

# おわりに


` jax.experimental.loops` に色々出てるから今後のアップデートでもっと使い勝手が良くなるかも．

# 参考文献

- [jax.experimental.loops module](https://jax.readthedocs.io/en/latest/jax.experimental.loops.html)
- [Best practice: scan vs fori_loop/while_loop](https://github.com/google/jax/discussions/3850)
- [jax.lax.scan](https://jax.readthedocs.io/en/latest/_autosummary/jax.lax.scan.html)
- [XLA（Accelerated Linear Algebra）](https://www.tensorflow.org/xla)
- [JAX reference documentation](https://jax.readthedocs.io/en/latest/index.html)
- []()
