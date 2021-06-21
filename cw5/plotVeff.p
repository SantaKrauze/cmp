set terminal png size 1000,600
set output "veff.png"

set xrange [0:30]
set yrange [-500:500]

f(x)=10000/(20*(x**2))-1000/x
plot f(x) title "H(r)"
