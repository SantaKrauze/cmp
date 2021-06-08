#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

from math import sin,cos,sqrt
from ivp2d import rk4_2d
import matplotlib.pyplot as plt
import sys

def dfalfa(t,alfa,omega):
    return omega

def dfomega(t,alfa,omega):
    return -(g/l)*sin(alfa)


frEtop = 1
g = 9.81
tE = 20
np = 100
l = 1.
m = 1.
E0 = frEtop*m*2.*l*g
t0 = 0.
alfa0 = 0.
omega0 = sqrt(2.*E0/m)/l
T = []
h = (tE-t0)/np

t,alfa,omega=rk4_2d(t0,tE,np,alfa0,omega0,dfalfa,dfomega)
Etot=[0.5*m*l*l*om**2+m*g*l*(1.-cos(alf)) for om,alf in zip(omega,alfa)]
k=0
for i in range(10,len(omega)-1):
    if omega[i-1] <= omega[i] and omega[i] >= omega[i+1]:
        k = i
        break

T = t[k]

plt.title("E = "+str(frEtop)+", T = "+str(T))
plt.xlabel("t")
plt.ylabel("alpha")
plt.plot(t, alfa)
plt.show()
plt.title("E = "+str(frEtop)+", T = "+str(T))
plt.xlabel("t")
plt.ylabel("omega")
plt.plot(t, omega)
plt.show()
