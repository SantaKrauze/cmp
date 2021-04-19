from deriv import fp3,fpp3,fun2
from math import log
import matplotlib.pyplot as plt

h = .1
hMin = .00000000000000001
logValues=[]
fp3Values=[]
fpp3Values=[]

while h >= hMin:
    logValues.append(-log(h))
    fp3Values.append(fp3(1,h,fun2))
    fpp3Values.append(fpp3(1,h,fun2))
    h /= 2

plt.plot(logValues,fp3Values)
plt.grid(1)
plt.title("sin(2x+1); x = 1")
plt.xlabel("-log(h)")
plt.ylabel("f '(h)")
plt.show()
plt.plot(logValues,fpp3Values)
plt.grid(1)
plt.title("sin(2x+1); x = 1")
plt.xlabel("-log(h)")
plt.ylabel("f ''(h)")
plt.show()
