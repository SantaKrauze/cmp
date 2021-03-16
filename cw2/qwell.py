#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

from math import sin,cos,sqrt
from fzero import bisek
import matplotlib.pyplot as plt
def feven(E):
    k=sqrt(2.*(Vo+E))
    return sin(k*a/2.)-cos(k*a/2.)*sqrt(-2.*E)/k

def fodd(E):
    k=sqrt(2.*(Vo+E))
    return sin(k*a/2.)+cos(k*a/2.)*k/sqrt(-2.*E)

oddFile=open("tableOdd","w")
evenFile=open("tableEven","w")

Vo=10.
a=2.
np=1000

h=Vo/np
dE=Vo/100.
tol=Vo/1000.
E1=-Vo+0.00001*Vo
E2=E1+dE

zero=[]
oddplot=[]
evenplot=[]
energies=[]

for i in range(1,np-1):
    E=-Vo+i*h
    energies.append(E)
    odd=fodd(E)
    even=feven(E)
    oddplot.append(odd)
    evenplot.append(even)

    oddFile.write(str(E)+" "+str(odd)+"\n")
    evenFile.write(str(E)+" "+str(even)+"\n")

evenFile.close()
oddFile.close()

while (E2<0.):
    if (feven(E1)*feven(E2)<0.):
        zero.append(bisek(E1,E2,tol,feven))

    if (fodd(E1)*fodd(E2)<0.):
    	zero.append(bisek(E1,E2,tol,fodd))

    E1=E2
    E2=E1+dE

plt.plot(evenplot,energies,'b-')
plt.show()
plt.plot(oddplot,energies,'b-')
plt.show()

print(zero)
