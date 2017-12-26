# gnuplotの設定
reset
set nokey                 # 凡例の非表示
set xrange [-4.0:4.0]     # x軸方向の範囲の設定
set yrange [-4.0:4.0]     # y軸方向の範囲の設定
set zrange [-2.0:2.0]     # z軸方向の範囲の設定

set hidden3d              # 隠線処理の設定

set term gif animate      # 出力をgifアニメに設定
set output "sample.gif"   # 出力ファイル名の設定

# 変数の設定
n0 = 0   # ループ変数の初期値
n1 = 89  # ループ変数の最大値
dn = 1   # ループ変数の増加間隔

# ループの開始
load "animation.plt"
