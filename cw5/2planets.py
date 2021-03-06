#!/usr/bin/python
# M. P. Polak & P. Scharoch 2017

# The code for introduction of the second planet is commented out

import matplotlib.pyplot as plt
from math import sqrt, floor

#def F(x1,y1,forces):
def F(x1,y1,x2,y2,forces):
	r1q = (x1*x1+y1*y1)**(1.5)
	r2q = (x2*x2+y2*y2)**(1.5)
	r12q = ((x2-x1)**2+(y2-y1)**2)**(1.5)
	forces[0] = -G*M*m1*x1/r1q+G*m1*m2*(x1-x2)/r12q
	forces[1] = -G*M*m1*y1/r1q+G*m1*m2*(x1-x2)/r12q
	forces[2] = -G*M*m2*x2/r2q+G*m1*m2*(x1-x2)/r12q
	forces[3] = -G*M*m2*y2/r2q+G*m1*m2*(y1-y2)/r12q
	return forces

#def EL(x1,y1,v1x,v1y,enemom):
def EL(x1,y1,x2,y2,v1x,v1y,v2x,v2y,enemom):
	r1 = (x1*x1+y1*y1)**(1./2.)
	v1s = v1x*v1x+v1y*v1y
	r2 = (x2*x2+y2*y2)**(1./2.)
	r12 = ((x2-x1)**2+(y2-y1)**2)**(1./2.)
	v2s = v2x*v2x+v2y*v2y
	enemom[0] = m1*v1s/2.-G*m1*M/r1
	enemom[1] = (x1*v1y*m1-y1*v1x*m1)
	enemom[0] = m1*v1s/2.+m2*v2s/2.-G*m1*M/r1-G*m2*M/r2-G*m1*m2/r12
	enemom[1] = (x1*v1y*m1-y1*v1x*m1)+(x2*v2y*m2-y2*v2x*m2)
	return enemom

x1 = [0.0]*3
y1 = [0.0]*3
x2 = [0.0]*3
y2 = [0.0]*3

G = 1
M = 100

m1 = 10
x1[0] = 5
y1[0] = 0
v1x = 0
v1y = 2

m2 = .1
x2[0] = 4.5
y2[0] = 0
v2x = 0
v2y = -2.5

tS = 0
tE = 300
Np = 5000

forces = [tS]*2*4
enemom = [tS]*2

dt = (tE-tS)/Np
dt2 = dt*dt

tarr = []
x1arr = []
y1arr = []
x2arr=[]
y2arr = []
enearr = []
momarr = []
#F(x1[0],y1[0],forces)
F(x1[0],y1[0],x2[0],y2[0],forces)
#EL(x1[0],y1[0],v1x,v1y,enemom)
EL(x1[0],y1[0],x2[0],y2[0],v1x,v1y,v2x,v2y,enemom)

x1[1] = x1[0]+v1x*dt+0.5*(forces[0]/m1)*dt2
y1[1] = y1[0]+v1y*dt+0.5*(forces[1]/m1)*dt2
x2[1] = x2[0]+v2x*dt+0.5*(forces[2]/m2)*dt2
y2[1] = y2[0]+v2y*dt+0.5*(forces[3]/m2)*dt2

tarr.append(0.)
x1arr.append(x1[1])
y1arr.append(y1[1])
x2arr.append(x2[1])
y2arr.append(y2[1])
enearr.append(enemom[0])
momarr.append(enemom[1])

for n in range(1,Np-1):
    t = 0.0+n*dt
    tarr.append(t)
    #F(x1[1],y1[1],forces)
    F(x1[1],y1[1],x2[1],y2[1],forces)

    x1[2] = 2.0*x1[1]-x1[0]+dt2*forces[0]/m1
    y1[2] = 2.0*y1[1]-y1[0]+dt2*forces[1]/m1
    x2[2] = 2.0*x2[1]-x2[0]+dt2*forces[2]/m2
    y2[2] = 2.0*y2[1]-y2[0]+dt2*forces[3]/m2

    v1x = (x1[2]-x1[0])/2.0/dt
    v1y = (y1[2]-y1[0])/2.0/dt
    v2x = (x2[2]-x2[0])/2.0/dt
    v2y = (y2[2]-y2[0])/2.0/dt

    #EL(x1[2],y1[2],v1x,v1y,enemom)
    EL(x1[2],y1[2],x2[2],y2[2],v1x,v1y,v2x,v2y,enemom)

    x1arr.append(x1[1])
    y1arr.append(y1[1])
    x2arr.append(x2[1])
    y2arr.append(y2[1])
    enearr.append(enemom[0])
    momarr.append(enemom[1])

    x1[0] = x1[1]
    y1[0] = y1[1]
    x2[0] = x2[1]
    y2[0] = y2[1]

    x1[1] = x1[2]
    y1[1] = y1[2]
    x2[1] = x2[2]
    y2[1] = y2[2]

H = []
r = []
i = .1
L = momarr[len(momarr)-1]
while i < 40:
    #r1 = sqrt(x1[i]*x1[i]+y1[i]*y1[i])
    #r2 = sqrt(x2[i]*x2[i]+y2[i]*y2[i])
    #r12 = sqrt((x2-x1)**2+(y2-y1)**2)
    #r.append(sqrt((x1[i])**2 + (y1[i])**2))
    L = 200
    #L = (x1[i]*v1y*m1-y1[i]*v1x*m1)+(x2[i]*v2y*m2-y2[i]*v2x*m2)
    #print(momarr)
    r.append(i)
    H.append((L**2)/(2*m1*i**2) - (G*m1*M/i))
    i += .1

#print(L)

plt.title("dt: " +str(dt))
plt.ylabel("y")
plt.xlabel("x")
plt.ylim(-50,50)
plt.xlim(-10,30)
plt.plot(x1arr, y1arr)
plt.plot(x2arr, y2arr)
plt.show()

plt.title("dt: " +str(dt))
plt.ylabel("M")
plt.xlabel("t")
plt.plot(tarr, momarr)
plt.show()

plt.title("dt: " +str(dt))
plt.ylabel("E")
plt.xlabel("t")
plt.plot(tarr, enearr)
plt.show()
