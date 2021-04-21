from deriv import fp3,fpp3,fun2
from math import log10, floor
import matplotlib.pyplot as plt

hMin = floor(-log10(.000000000000000001))
logValues=[]
fp3Values=[]
fpp3Values=[]

for i in range (1,hMin):
    h = 10**-i
    logValues.append(-log10(h))
    fp3Values.append(fp3(1,h,fun2))
    fpp3Values.append(fpp3(1,h,fun2))

plt.plot(logValues,fp3Values)
plt.grid(1)
plt.title("f = sin(2x+1); x = 1")
plt.xlabel("-log(h)")
plt.ylabel("f '(h)")
plt.show()
plt.plot(logValues,fpp3Values)
plt.grid(1)
plt.title("f = sin(2x+1); x = 1")
plt.xlabel("-log(h)")
plt.ylabel("f ''(h)")
plt.show()
