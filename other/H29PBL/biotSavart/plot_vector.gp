set style arrow 1
set xrange [-3.0:3.0]
set yrange [-3.0:3.0]
set zrange [-3.0:3.0]

set palette rgbformulae 30,31,32
set ticslevel 0

splot "mission1.dat" u 1:2:3:4:5:6 w vectors arrowstyle 1
