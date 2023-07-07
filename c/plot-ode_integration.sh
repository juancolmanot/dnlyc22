#!/usr/bin/gnuplot

set terminal pdfcairo size 9,12 font 'Arial, 30'

set output 'plots/plot_ode_integration_step.pdf'

set xtics font 'Arial, 22'
set ytics font 'Arial, 22'

set multiplot layout 2,1 rowsfirst

set title 'Integration step with driver'
set ylabel 'x'
set xlabel 't'

p 'datafiles/evolution_sys1_driver.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys2_driver.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys3_driver.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys4_driver.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys5_driver.dat' u 1:3 notitle w l lw 1.5

set title 'Integration step with evolve'
set ylabel 'x'
set xlabel 't'

set logscale

p 'datafiles/evolution_sys1_evolve.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys2_evolve.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys3_evolve.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys4_evolve.dat' u 1:3 notitle w l lw 1.5, \
'datafiles/evolution_sys5_evolve.dat' u 1:3 notitle w l lw 1.5

unset multiplot