#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017
import matplotlib.pyplot as plt
from math import exp

def euler(a, b, n, y0, fun):
    h = (b-a)/n
    yp = [y0]
    xp = [a]
    for i in range(0, n):
        yp.append(yp[i]+h*fun(xp[i],yp[i]))
        xp.append(xp[i]+h)
    return xp,yp

def rk4(a, b, n, y0, fun):
    h = (b-a)/n
    yp = [y0]
    xp = [a]
    for i in range(0, n):
        k1 = h*fun(xp[i],yp[i])
        k2 = h*fun(xp[i]+h/2.,yp[i]+k1/2.)
        k3 = h*fun(xp[i]+h/2.,yp[i]+k2/2.)
        k4 = h*fun(xp[i]+h,yp[i]+k3)
        yp.append(yp[i]+(k1+2.*k2+2.*k3+k4)/6.)
        xp.append(xp[i]+h)
    return xp,yp

def ab3(a, b, n, y0, fun):
    h = (b-a)/n
    #yp = list(y0,y0+h,y0+h+h)
    yp = [y0, y0+h, y0+h+h]
    xp = [a,a+h,a+h+h]
    for i in range(2,n):
        yp.append(yp[i]+h/12.*(23.*fun(xp[i],yp[i])-16.*fun(xp[i-1],yp[i-1])+5.*fun(xp[i-2],yp[i-2])))
        xp.append(xp[i]+h)
    return xp,yp

def dFun(x, y):
    return y

def fun(x):
    return exp(x)

if __name__ == "__main__":
    a = 0
    b = 50
    n = 100
    y0 = 1
    x = []
    y = []
    h = (b-a)/n
    i = 0
    while i <= b:
        x.append(i)
        y.append(fun(i))
        i += h

    eulerX, eulerY = euler(a, b, n, y0, dFun)
    rkX, rkY = rk4(a, b, n, y0, dFun)
    abX, abY = ab3(a, b, n, y0, dFun)
    plt.xlabel("x")
    plt.xlim([45,50])
    plt.ylabel("y")
    plt.plot(x, y, label='exp(x)')
    plt.plot(eulerX, eulerY, label='euler')
    plt.plot(rkX, rkY, label='rk4')
    plt.plot(abX, abY, label='ab3')
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)
    #plt.rcParams["figure.figsize"] = (40,30)
    plt.show()
