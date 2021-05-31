import matplotlib.pyplot as plt
from math import exp, log10
from ivp import euler, ab3, rk4

def dFun(x, y):
    return y

def fun(x):
    return exp(x)

if __name__ == "__main__":
    a = 0
    b = 1
    n = 100000
    y0 = 1
    h = (b-a)/n
    i = 1
    logH=[]
    eulerVals=[]
    abVals=[]
    rkVals=[]
    while i <= n:
        eulerX, eulerY = euler(a, b, i, y0, dFun)
        rkX, rkY = rk4(a, b, i, y0, dFun)
        abX, abY = ab3(a, b, i, y0, dFun)
        logH.append(-log10((b-a)/i))
        eulerVals.append(eulerY[i])
        abVals.append(abY[i])
        rkVals.append(rkY[i])
        i *= 2

    plt.plot(logH, eulerVals, label='euler')
    plt.plot(logH, rkVals, label='rk4')
    plt.plot(logH, abVals, label='ab3')
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)
    plt.show()
