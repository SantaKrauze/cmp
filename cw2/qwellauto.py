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

VOpt=0
aOpt=0
En1=.5
En2=.125
delta = .1
#V=.65
#a=3.95
np=1000
zeroOdd=0.
zeroEven=0.
zero=[]
oddplot=[]
evenplot=[]
energies=[]

oddFile=open("tableOddAuto.out","w")
evenFile=open("tableEvenAuto.out","w")

for i in range (0,10):
    a = i
    for j in range (0,5):
        V = j
        h = V / np
        dE = V / 100.
        tol = V / 1000.
        E1 = -V + 0.00001 * V
        E2=E1+dE
        while (E2<0.):
            if (feven(E1)*feven(E2) < 0.):
                zeroEven = (bisek(E1,E2,tol,feven))

                if (zeroEven-En1-delta < 0.):
                    VOpt = V
                    aOpt = a
                    zero.append(zeroEven)

            if (fodd(E1)*fodd(E2) < 0.):
    	        zeroOdd = (bisek(E1,E2,tol,fodd))

                if (zeroOdd-En2-delta < 0.):
                    VOpt = V
                    aOpt = a
                    zero.append(zeroOdd)
            
            E1 = E2
            E2 = E1 + dE

        #for i in range(1,np-1):
            #E=-V+i*h
            #energies.append(E)
            #odd=fodd(E)
            #even=feven(E)
            #oddplot.append(odd)
            #evenplot.append(even)
            #oddFile.write(str(E)+" "+str(odd)+"\n")
            #evenFile.write(str(E)+" "+str(even)+"\n")
        
evenFile.close()
oddFile.close()

#print(zero)

plt.plot(energies,evenplot)
plt.plot(energies,oddplot)
plt.grid(True)
plt.xlabel("E")
plt.ylabel("F(E)")
#plt.show()
