#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

from math import sin,cos,sqrt
from fzero import bisek
import matplotlib.pyplot as plt

def feven(E):
    k=sqrt(2.*(V+E))
    return sin(k*a/2.)-cos(k*a/2.)*sqrt(-2.*E)/k

def fodd(E):
    k=sqrt(2.*(V+E))
    return sin(k*a/2.) + cos(k*a/2.)*k/sqrt(-2.*E)

En1=.5
En2=.125
delta = .1

VOpt=0
aOpt=0
V = delta
a = delta
np=1000
zeroOdd=0.
zeroEven=0.
zero=[]
oddplot=[]
evenplot=[]
energies=[]

while V < 3:
    while a < 5:
        h = V / np
        dE = V / 100.
        tol = V / 1000.
        E1 = -V + 0.00001 * V
        E2=E1+dE
        while (E2<0.):
            if (feven(E1)*feven(E2) < 0.):
                zeroEven = (bisek(E1,E2,tol,feven))
                #print(zeroEven)
                if zeroEven + delta > En1 or zeroEven - delta < En1:
                    VOpt = V
                    aOpt = a
                    zero.append(zeroEven)
                    #print(VOpt)

            if (fodd(E1)*fodd(E2) < 0.):
                zeroOdd = (bisek(E1,E2,tol,fodd))
                #print(zeroOdd)
                if zeroOdd + delta > En2 or zeroOdd - delta < En2:
                    VOpt = V
                    aOpt = a
                    zero.append(zeroOdd)
                    #print(VOpt)
            
            E1 = E2
            E2 = E1 + dE
        a += delta
    V += delta
    
print(VOpt)
print(aOpt)
print(zero)

oddFile=open("tableOddAuto.out","w")
evenFile=open("tableEvenAuto.out","w")

for i in range(1,np-1):
    E=-V+i*h
    energies.append(E)
    odd=fodd(E)
    even=feven(E)
    oddplot.append(odd)
    evenplot.append(even)
    oddFile.write(str(E)+" "+str(odd)+"\n")
    evenFile.write(str(E)+" "+str(even)+"\n")

evenFile.close()
oddFile.close()

plt.plot(energies,evenplot)
plt.plot(energies,oddplot)
plt.grid(True)
plt.xlabel("E")
plt.ylabel("F(E)")
#plt.show()
