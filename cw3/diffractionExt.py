from math import cos,sin,pi,sqrt
from quadrat import simpson
import matplotlib.pyplot as plt

def real_amp(x):
	r = sqrt(d*d+(y-x)**2)
	return ampl*cos(k*r)/(sqrt(r))

def imag_amp(x):
	r = (d*d+(y-x)**2)**(1./2.)
	return ampl*sin(k*r)/(sqrt(r))

ndiv = 100
ampl = 1.
lmbd = 1.
k = 2.*pi/lmbd
d = 20.
a = 5.
yl = -50.
yr = 50.
ny = 100

hy = (yr-yl)/ny

yarr = []
i1arr = []
i2arr = []

for iy in range(1, ny):
    y = yl+(iy-1.)*hy 
    i1 = simpson(-a/2., a/2., ndiv, real_amp)**2+simpson(-a/2, a/2, ndiv, imag_amp)**2
    i2 = simpson(-a/2., -a/4., ndiv, real_amp)**2 + simpson(-a/2, -a/4, ndiv, imag_amp)**2 + simpson(a/4., a/2., ndiv, real_amp)**2 + simpson(a/4, a/2, ndiv, imag_amp)**2
    yarr.append(y)
    i1arr.append(i1)
    i2arr.append(i2)

plt.plot(yarr,i1arr)
plt.plot(yarr,i2arr)
plt.grid(1)
plt.title("a = "+str(a)+" ,d = "+str(d)+" ,lambda = "+str(lmbd))
plt.xlabel("y")
plt.ylabel("I")
plt.show()
