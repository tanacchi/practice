# gnuplotの設定
reset
set nokey                 # 凡例の非表示
set ticslevel 0
set xlabel "x"
set ylabel "y"
set zlabel "z"
set xrange [-3.0:3.0]     # x軸方向の範囲の設定
set yrange [-3.0:3.0]     # y軸方向の範囲の設定
set zrange [-2.0:2.0]     # z軸方向の範囲の設定

set term gif animate optimize \
    delay 50 \
    size 720,540        # 出力をgifアニメに設定
set output "sample.gif"   # 出力ファイル名の設定

# 変数の設定
n0 = 0    # ループ変数の初期値
n1 = 89   # ループ変数の最大値
dn = 5    # ループ変数の増加間隔

# ループの開始
load "animation.plt"
