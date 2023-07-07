#!/usr/bin/gnuplot

set terminal pdfcairo size 9,12 font 'Arial, 30'

set output 'plots/plot_system_bifurcation_1.pdf'

set xtics font 'Arial, 22'
set ytics font 'Arial, 22'

set title 'Diagrama de bifuración para el parámetro {/Symbol m}'
set ylabel 'x'
set xlabel '{/Symbol m}'

p 'datafiles/bifurcation_sys1_driver.dat' u 1:2 notitle w p pt 6 ps 0.05 lc rgb 'black'

