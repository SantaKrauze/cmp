from quadrat import simpson
from math import sqrt, log
import matplotlib.pyplot as plt

def fun(x):
    return 4*sqrt(1-x*x)

print(simpson(0,1,1000000,fun))
