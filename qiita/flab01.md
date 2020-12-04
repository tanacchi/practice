この記事は[九工大古川研 Advent Calendar 2020](https://qiita.com/advent-calendar/2020/flab) 8日目の記事です．
本記事は古川研究室の学生が学習の一環として書いたものです．
内容が曖昧であったり表現が多少異なったりする場合があります．


<!--
\end{align}
```

```math
\begin{align} 
-->

## まえがき
局所線形回帰について調べました．
研究室に入りたての私でも理解できるような、
ちょっとクドいくらい丁寧に説明できたらと思っております。

今回は線形回帰の拡張として解説します．

## 局所線形回帰とは
線形


[$ x], [$ y] のペアを入力として
これを直線で近似します．

直線の式は以下のように書けます．
推定値は [$ \hat{y}]

```math
\begin{align}
\hat{y} &= a_1 x + a_0 \\
&= \left( \begin{array}{cc} 1 & x \\ \end{array} \right)
\left( \begin{array}{c} a_0 \\ a_1 \end{array} \right) \\
&= \boldsymbol{x}^T \boldsymbol{a}
\end{align}
```

[$ a_1] が傾き（1次のパラメータ），[$ a_0] が切片（0次のパラメータ）です．

```math 
\begin{align}
E &= \sum_i^n ( y_i - \hat{y}_i )^2 \\
&= \sum_i^n ( y_i - \boldsymbol{x}_i^T\boldsymbol{a} )^2 \\
\end{align}
```

ここで，敢えて [$ \sum] を外した形で書いてみます．



```math
\begin{align} 
E &=  ( y_1 - \boldsymbol{x}_1^T\boldsymbol{a} )^2 + \cdots + ( y_i - \boldsymbol{x}_i^T\boldsymbol{a} )^2
\end{align}
```

最小二乗法では
[$ E] を最小にするようなパラメータ [$ \boldsymbol{a}] を求めることになります．

そしてこれを行列積の形で表現すると以下のようになります．

```math
\begin{align} 
E &= \left( \begin{array}{cccc} y_1 - \boldsymbol{x}_1^T\boldsymbol{a} & \cdots & y_n - \boldsymbol{x}_n^T\boldsymbol{a}  \end{array} \right)
\left( \begin{array}{c} y_1 - \boldsymbol{x}_1^T\boldsymbol{a} \\ \vdots \\ y_n - \boldsymbol{x}_n^T\boldsymbol{a} \\ \end{array} \right) \\
\end{align}
```

ここで，

```math
\begin{align} 
\boldsymbol{y} &:= \left( \begin{array}{c} y_1 \\ \vdots \\ y_n \\ \end{array} \right)\\

X &:= \left( \begin{array}{c} \boldsymbol{x}_1^T \\ \vdots \\ \boldsymbol{x}_n^T \\ \end{array} \right)
\end{align}
```

というふうにおくと，

```math
\boldsymbol{y} - \boldsymbol{X} \boldsymbol{a} = \left( \begin{array}{c} y_1 \\ \vdots \\ y_n \\ \end{array} \right) - \left( \begin{array}{c} \boldsymbol{x}_1^T \\ \vdots \\ \boldsymbol{x}_n^T \\ \end{array} \right) \boldsymbol{a} = \begin{align} 
\left( \begin{array}{c} y_1 - \boldsymbol{x}_1^T\boldsymbol{a} \\ \vdots \\ y_n - \boldsymbol{x}_n^T\boldsymbol{a} \\ \end{array} \right)
\end{align}
```

すなわち先程の式は以下のように書けます．

```math
\begin{align} 
E &= \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)^T
\left(\boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right) \\
&= \left\|\boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right\|^2
\end{align}
```

ユークリッドノルムの二乗ですね．

[The Matrix Cookbook](https://www.math.uwaterloo.ca/~hwolkowi/matrixcookbook.pdf)

## （普通の）線形回帰を解く

読み飛ばしてもらって大丈夫です．
いわゆる最小二乗法を行列の形で解きます．


```math
\begin{align} 
\frac{\partial}{\partial \boldsymbol{a}} E
&= \frac{\partial}{\partial \boldsymbol{a}}\left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)^T
\left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right) \\
&=  \frac{\partial}{\partial \boldsymbol{a}}
\left( \boldsymbol{y}^T - \boldsymbol{a}^T\boldsymbol{X}^T \right)
\left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right) \\
&= \frac{\partial}{\partial \boldsymbol{a}}
\left( \boldsymbol{y}^T\boldsymbol{y}
- \boldsymbol{y}^T\boldsymbol{X}\boldsymbol{a}
- \boldsymbol{a}^T\boldsymbol{X}^T\boldsymbol{y}
+ \left(\boldsymbol{X} \boldsymbol{a} \right)^T \left(\boldsymbol{X} \boldsymbol{a} \right)
\right) \\
&= 0 - \boldsymbol{X}^T \boldsymbol{y} - \boldsymbol{X}^T \boldsymbol{y} + 2 \boldsymbol{X}^T \boldsymbol{X} \boldsymbol{a} \\
&= - 2 \boldsymbol{X}^T \boldsymbol{y} - 2 \boldsymbol{X}^T \boldsymbol{X} \boldsymbol{a}
\end{align}
```

となります．

```math
\frac{\partial}{\partial \boldsymbol{a}} E = 0
```

極値を求めますと，

```math
\begin{align}
- 2 \boldsymbol{X}^T \boldsymbol{y} - 2 \boldsymbol{X}^T \boldsymbol{X} \boldsymbol{a} &= 0 \\
2\boldsymbol{X}^T \boldsymbol{X} \boldsymbol{a} &= 2 \boldsymbol{X}^T \boldsymbol{y} \\
\boldsymbol{a} &= \left( \boldsymbol{X}^T \boldsymbol{X} \right)^{-1}\boldsymbol{X}^T \boldsymbol{y}
\end{align}
```

となります．
めでたしめでたし．
また，

```math
\boldsymbol{X}^{\dagger} = \begin{align}
\left( \boldsymbol{X}^T \boldsymbol{X} \right)^{-1}\boldsymbol{X}^T
\end{align}
```

ムーアペンローズの逆行列です．

```math 
\hat{\boldsymbol{y}} = \boldsymbol{X}^{\dagger}\boldsymbol{a}
```

## 局所線形回帰に拡張

ここからが本題です．

```math 
\begin{align}
E &= \sum_i^n k(x^\ast, x_i) ( y_i - \boldsymbol{x}_i^T\boldsymbol{a} )^2 \\
&= \left( \begin{array}{ccc} y_1 - \boldsymbol{x}_1^T\boldsymbol{a} & \cdots & y_n - \boldsymbol{x}_n^T\boldsymbol{a} \end{array} \right)
\left( \begin{array}{ccc}
k(x^\ast, x_1) & & \huge{0} \\
 & \ddots  & \\
\huge{0} & & k(x^\ast, x_n) \\
\end{array} \right)
\left( \begin{array}{c} y_1 - \boldsymbol{x}_1^T\boldsymbol{a} \\ \vdots \\ y_n - \boldsymbol{x}_n^T\boldsymbol{a} \\ \end{array} \right) \\
\end{align}
```

ここで先ほどと同じように [$ y, X] を定義し

```math
\begin{align}
\boldsymbol{W} = \left( \begin{array}{ccc}
k(x^\ast, x_1) & & \huge{0} \\
 & \ddots  & \\
\huge{0} & & k(x^\ast, x_n) \\
\end{array} \right)
\end{align}
```

とおきます．

```math
\begin{align}
 &= \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)^T
\boldsymbol{W} \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)
\end{align}
```

[$ \boldsymbol{a}] で偏微分すると以下のようになります．


```math 
\begin{align}
\frac{\partial}{\partial \boldsymbol{a}} E &= \frac{\partial}{\partial \boldsymbol{a}} \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)^T
\boldsymbol{W} \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)\\
&= \frac{\partial}{\partial \boldsymbol{a}} \left( \boldsymbol{y}^T - \boldsymbol{a}^T\boldsymbol{X}^T \right) 
\boldsymbol{W} \left( \boldsymbol{y} - \boldsymbol{X}\boldsymbol{a} \right)\\
&=  \frac{\partial}{\partial \boldsymbol{a}}\left(
\boldsymbol{y}^T \boldsymbol{W} \boldsymbol{y}
- \boldsymbol{y}^T \boldsymbol{W} \boldsymbol{X}\boldsymbol{a}
- \boldsymbol{a}^T\boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y} 
+ (\boldsymbol{X}\boldsymbol{a})^T \boldsymbol{W} \boldsymbol{X}\boldsymbol{a} \right)\\
&= 0 - \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y} - \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y}  + 2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \boldsymbol{a} \\
&= - 2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y} + 2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \boldsymbol{a} \\
2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \boldsymbol{a} &= 2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y} \\
\boldsymbol{a} &= \left(  \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \right)^{-1} \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y}
\end{align}
```

```math
\frac{\partial}{\partial \boldsymbol{a}} E = 0
```

となるような [$ \boldsymbol{a}] を求めていきます．

```math
\begin{align}
2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \boldsymbol{a} &= 2 \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y} \\
\boldsymbol{a} &= \left(  \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{X} \right)^{-1} \boldsymbol{X}^T \boldsymbol{W} \boldsymbol{y}
\end{align}
```


## 実際に回帰してみる

<!--
## Nadaraya-Watson との関係
どちらも局所多項式回帰の特別なパターン
比較

-->

## ちなみに

## おわりに

## 付録：実装まとめ

