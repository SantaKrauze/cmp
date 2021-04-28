#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017
import matplotlib.pyplot as plt

def euler(a,b,n,y0,fun):
    h=(b-a)/n
    yp=[y0]
    xp=[a]
    for i in range(0,n):
        yp.append(yp[i]+h*fun(xp[i],yp[i]))
        xp.append(xp[i]+h)
    return xp,yp
        
def rk4(a,b,n,y0,fun):
    h=(b-a)/n
    yp=[y0]
    xp=[a]
    for i in range(0,n):
        k1=h*fun(xp[i],yp[i])
        k2=h*fun(xp[i]+h/2.,yp[i]+k1/2.)
        k3=h*fun(xp[i]+h/2.,yp[i]+k2/2.)
        k4=h*fun(xp[i]+h,yp[i]+k3)
        yp.append(yp[i]+(k1+2.*k2+2.*k3+k4)/6.)
        xp.append(xp[i]+h)
    return xp,yp

def ab3(a,b,n,y0,fun):
    h=(b-a)/n
    yp=list(y0)
    xp=[a,a+h,a+h+h]
    for i in range(2,n):
        yp.append(yp[i]+h/12.*(23.*fun(xp[i],yp[i])-16.*fun(xp[i-1],yp[i-1])+5.*fun(xp[i-2],yp[i-2])))
        xp.append(xp[i]+h)
    return xp,yp

def fun(x,y):
    return y

if __name__ == "__main__":
    plt.plot(euler(0,3,10,0,fun))
    #plt.plot(rk4(0,3,10,0,fun))
    #plt.plot(ab3(1,0,1,0,fun))
    plt.show()
    #print(euler(0,3,10,1,fun))
    #print(rk4(1,0,1000,0,fun))
    #print(ab3(1,10,1000,0,fun))
