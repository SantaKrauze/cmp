set surface 
set contour surface
set dgrid3d 
set terminal png size 1200,1000
set output "2d.png"

set view 65,260,1,1
set xrange [-10:10]
set yrange [-10:10]

set xlab 'x'
set ylab 'y'
set zlab 'z'

splot '2dtableout' u 1:2:3 with lines title 'sin(sqrt(x^2+y^2))/sqrt(x^2+y^2)'
