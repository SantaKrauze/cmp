#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017
from math import exp

def simpson(xl, xr, ndiv, fun):
	h=(xr-xl)/ndiv/2.
	integ=0.
	for i in range(0,ndiv):
		integ=integ+2.*h*(fun(xl+i*2.*h)+4.*fun(xl+i*2.*h+h)+fun(xl+i*2.*h+2*h))/6.
	return integ

def fun(x):
    return exp(x)

if __name__ == "__main__":
    print(simpson(0,1,1000,fun))
