# ループ処理
if(exist("n")==0 || n<0) n = n0  # ループ変数の初期化

# 視線の変更
set view n+5, n*3.0, 1, 1;     # 視点の変更

# プロット
splot 'mission3xy.dat'

# ループ処理
n = n + dn            # ループ変数の増加
if ( n < n1 ) reread  # ループの評価
undefine n            # ループ変数の削除
