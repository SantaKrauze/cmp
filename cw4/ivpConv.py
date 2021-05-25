#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017
import matplotlib.pyplot as plt
from math import exp, log10
from ivp import euler, rk4, ab3

def dFun(x, y):
    return y

def fun(x):
    return exp(x)

if __name__ == "__main__":
    a = 0
    b = 1
    n = 100
    y0 = 1
    rk = []
    ab = []
    euler = []
    logH = []
    h = (b-a)/n
    i = 1

    eulerX, eulerY = euler(a, b, i, y0, dFun)
    rkX, rkY = rk4(a, b, i, y0, dFun)
    abX, abY = ab3(a, b, i, y0, dFun)
    print(rkY[i])
    #euler.append(eulerY[i])
    #rk.append(rkY[i])
    #ab.append(abY[i])
    #logH.append(log10((b-a)/i))
        #eulerX, eulerY, rkX, rkY, abX, abY = 0
    i *= 2

    plt.plot(logH, euler, label='euler')
    plt.plot(logH, rk, label='rk4')
    plt.plot(logH, ab, label='ab3')
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)
    #plt.rcParams["figure.figsize"] = (40,30)
    plt.show()
