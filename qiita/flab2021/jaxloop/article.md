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

[]
