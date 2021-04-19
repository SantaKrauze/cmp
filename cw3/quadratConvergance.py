from quadrat import simpson,fun
from math import log
import matplotlib.pyplot as plt
import time

N=5
xl=0
xr=1
hValues=[]
logValues=[]
simpsonValues=[]
calcTimes=[]

while N <= 500000000:
    h = (xr-xl)/N/2
    hValues.append(h)
    logValues.append(-log(h))
    start = time.time()
    simpsonValues.append(simpson(xl,xr,N,fun))
    end = time.time()
    calcTimes.append(end-start)
    N *= 2

plt.plot(logValues,simpsonValues)
plt.grid(1)
plt.title("Nf = "+str(N))
plt.xlabel("-log(h)")
plt.ylabel("F")
plt.show()
plt.plot(logValues,calcTimes)
plt.grid(1)
plt.title("Nf = "+str(N))
plt.xlabel("-log(h)")
plt.ylabel("t(h)")
plt.show()
