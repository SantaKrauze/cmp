from quadrat import simpson,fun
from math import log10, floor
import matplotlib.pyplot as plt
import time

xl=0
xr=1
logValues=[]
simpsonValues=[]
calcTimes=[]
nMax = floor(log10(1000000000))

for i in range (1, nMax):
    N=10**i
    h = (xr-xl)/N/2
    logValues.append(-log10(h))
    start = time.time()
    simpsonValues.append(simpson(xl,xr,N,fun))
    end = time.time()
    calcTimes.append(end-start)

plt.plot(logValues,simpsonValues)
plt.grid(1)
plt.title("Nf = "+str(N))
plt.xlabel("-log(h)")
plt.ylim([0, 2])
plt.ylabel("F")
plt.show()
plt.plot(logValues,calcTimes)
plt.grid(1)
plt.title("Nf = "+str(N))
plt.xlabel("-log(h)")
plt.ylabel("t [s]")
plt.show()
