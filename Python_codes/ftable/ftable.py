#!/usr/bin/python

# M. P. Polak & P. Scharoch 2017

import matplotlib.pyplot as plt
from math import sin,cos

def function(x):
	return x*sin(x)

### INPUT

xl=-10.
xr=10.
npoints=1000

### INPUT

file=open("output.txt",'w')

h=(xr-xl)/(npoints-1)
xarr=[]
yarr=[]

for i in range(0,npoints+1):
        x=xl+i*h
        xarr.append(x)
        yarr.append(function(x))
#        file.write(str(x)+" "+str(function(x))+"\n") 
#        file.close()
plt.plot(xarr,yarr,'b-')
plt.show()
