#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

from math import cos,sin,pi,sqrt
from quadrat import simpson
import matplotlib.pyplot as plt

def real_amp(x):
	r = sqrt(d*d+(y-x)**2)
	return ampl*cos(k*r)/(sqrt(r))

def imag_amp(x):
	r = (d*d+(y-x)**2)**(1./2.)
	return ampl*sin(k*r)/(sqrt(r))

ndiv = 1000
ampl = 1
lmbd = 1
k = 2.*pi/lmbd
#d=50,a=2
d = 75
a = 4
yl = -100
yr = 100
ny = 1000

hy = (yr-yl)/ny

yarr = []
iarr = []

for iy in range(1, ny):
	y = yl+(iy-1.)*hy
	i = simpson(-a/2., a/2., ndiv, real_amp)**2+simpson(-a/2, a/2, ndiv, imag_amp)**2
	yarr.append(y)
	iarr.append(i)

ymin = lmbd*d/a
plt.plot(yarr,iarr)
plt.axvline(x = ymin, color='grey')
plt.grid(1)
plt.title("a = "+str(a)+" ,d = "+str(d)+" ,lambda = "+str(lmbd))
plt.xlabel("y")
plt.ylabel("I")
plt.show()
