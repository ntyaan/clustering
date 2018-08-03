set parametric
set angle degree
set urange [0:90]
set vrange [0:90]
set isosample 36,36
set view 60,130
set view equal xyz
set xlabel "x"
set ylabel "y"
set zlabel "z"
set ticslevel 0
set samples 1000
a=1
splot a*cos(u)*cos(v),a*sin(u)*cos(v),a*sin(v) notitle, "spherical.txt" 
set terminal pdf
set output "spherical.pdf"
replot
