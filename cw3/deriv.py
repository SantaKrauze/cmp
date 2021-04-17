#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017
from math import sin

def fp3(x,h,fun):
    return (fun(x+h)-fun(x-h))/2./h

def fpp3(x,h,fun):
    return (fun(x+h)+fun(x-h)-2.*fun(x))/h**2

def fun1(x):
    return 2*x*x + x - 1

def fun2(x):
    return sin(2*x+1)


if __name__ == "__main__":
    print("2*x^2+x-1")
    print(fp3(1,.01,fun1))
    print(fpp3(1,.01,fun1))

    print("sin(2x+1)")
    print(fp3(1,.01,fun2))
    print(fpp3(1,.01,fun2))
