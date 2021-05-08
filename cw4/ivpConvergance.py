from ivp import euler, rk4, ab3, dFun, fun
import matplotlib.pyplot as plt

N = 100
a = 1
b = 1
y0 = 1

eulerX = []
eulerY =[]
ab3X = []
ab3Y = []
rk4X = []
rk4Y = []

for i in range (1, N):
    #y1 of h, showing the last resoult of every method
