#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def rk4_2d(a,b,n,y1_0,y2_0,fun1,fun2):
    h=(b-a)/n
    yp_1=[y1_0]
    yp_2=[y2_0]
    xp=[a]
    for i in range(0,n):
        k1_1=h*fun1(xp[i],yp_1[i],yp_2[i])
        k1_2=h*fun2(xp[i],yp_1[i],yp_2[i])

        k2_1=h*fun1(xp[i]+h/2.,yp_1[i]+k1_1/2.,yp_2[i]+k1_2/2.)
        k2_2=h*fun2(xp[i]+h/2.,yp_1[i]+k1_1/2.,yp_2[i]+k1_2/2.)

        k3_1=h*fun1(xp[i]+h/2.,yp_1[i]+k2_1/2.,yp_2[i]+k2_2/2.)
        k3_2=h*fun2(xp[i]+h/2.,yp_1[i]+k2_1/2.,yp_2[i]+k2_2/2.)

        k4_1=h*fun1(xp[i]+h,yp_1[i]+k3_1,yp_2[i]+k3_2)
        k4_2=h*fun2(xp[i]+h,yp_1[i]+k3_1,yp_2[i]+k3_2)

        yp_1.append(yp_1[i]+(k1_1+2.*k2_1+2.*k3_1+k4_1)/6.)
        yp_2.append(yp_2[i]+(k1_2+2.*k2_2+2.*k3_2+k4_2)/6.)
        xp.append(xp[i]+h)
    return xp,yp_1,yp_2

def fun1(x, y1, y2):
    return y2

def fun2(x, y1, y2):
    return -k*y1

if __name__ == "__main__":
    a = 0
    b = 10
    n = 1000000
    k = 1
    m = 1
    y1_0 = 1
    y2_0 = -1
    E = []

    x, y1, y2 = rk4_2d(a, b, n, y1_0, y2_0, fun1, fun2)
    Ef = (m*(y2[n])**2)/2 + ((k*y1[n])**2)/2
    for i in range(len(x)):
        E.append(((m*y2[i])**2)/2 + ((k*y1[i])**2)/2)

    print(E)
    plt.title("Differential, n = "+str(n))
    plt.xlabel("x")
    plt.ylabel("y")
    plt.plot(x,y1)
    plt.show()
    plt.title("Energy, n = "+str(n))
    plt.xlabel("x")
    plt.ylabel("E")
    #plt.ylim([.95,1.05])
    plt.plot(x,E)
    plt.show()

    f = open("ivp2d_out.data","w")
    for i in range(len(x)):
        f.write(str(x[i]) + "\t" + str(y1[i]) + "\t" + str(y2[i]) + "\n")
    f.close()
