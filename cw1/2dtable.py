#!/usr/bin/python

# M. P. Polak & P. Scharoch 2017

import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from math import sin,cos,sqrt

def function(x,y):
    sqr=sqrt(x*x + y*y)
    return sin(sqr)/sqr

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
    file.write(str(x)+" "+str(y)+" "+str(function(x,y))+"\n") 
    #file.close()

fig=plt.figure()
#ax=plt.axes(projection='3d')
ax=fig.add_subplot(111,projection='3d')
#ax.plot_surface(xarr,yarr,zarr)
ax.set_title('sin(sqrt(x^2 + y^2))/sqrt(x^2 + y^2)')
ax.plot(xarr,yarr,zarr)
plt.show()
