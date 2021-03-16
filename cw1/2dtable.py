#!/usr/bin/python

# M. P. Polak & P. Scharoch 2017

import matplotlib.pyplot as plt
from math import sin,cos

def function(x,y):
    sqrt=sqrt(x^2+y^2)
	return sin(sqrt)/sqrt

xl=-10.
xr=10.
yl=-10.
yr=10.
npoints=1000

file=open("2dtableout",'w')

h=(xr-xl)/(npoints-1)
xarr=[]
yarr=[]
zarr=[]

for i in range(0,npoints+1):
    x=xl+i*h
    y=yl+i*h
    xarr.append(x)
    yarr.append(y)
    zarr.append(function(x,y))
    file.write(str(x)+" "+str(y)+" "+str(function(x,y))"\n") 
    #file.close()
plt.plot(xarr,yarr,zarr,'b-')
plt.show()
