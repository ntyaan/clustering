set yrange [0:100]
set xrange [0:100]
set zrange [0:100]
set view 60,130
set view equal xyz
set xlabel "x"
set ylabel "y"
set zlabel "z"
set parametric
set ticslevel 0
set samples 1000
splot  [0:100] [0:100] [0:100] u,v,100-u-v lc rgb "red" notitle, -u+100,u,0 lc rgb "red" notitle ,"multinomial.txt" 
set terminal pdf
set output "multinomial.pdf"
replot
