from deriv import fp3,fpp3,fun2
from math import log
import matplotlib.pyplot as plt

h=.1
hValues=[]
fpValues=[]
fppValues=[]

while h >= .00000000000000001:
    logH = -log(h)
    hValues.append(logH)
    fpValues.append(fp3(1,h,fun2))
    fppValues.append(fpp3(1,h,fun2))
    h /= 2

plt.plot(hValues,fpValues)
plt.grid(True)
plt.xlabel("log(h)")
plt.ylabel("f '(h)")
plt.show()
plt.plot(hValues,fppValues)
plt.grid(True)
plt.xlabel("log(h)")
plt.ylabel("f ''(h)")
plt.show()
