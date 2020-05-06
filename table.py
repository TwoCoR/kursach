#!/usr/bin/python
import matplotlib.pyplot as mpl
import math
f = open("table.txt",'r')
pl = [1,2,4,8,16,32,64,128,256,512,1024,2048]
pl1 = []
pl2 = []
pl3 = []
pl4 = []

for i in range(12):
   str = f.readline().split(" ")
   pl1.append(float(str[0]))
   pl2.append(float(str[1]))
   pl3.append(float(str[2]))
   pl4.append(float(str[3]))
mpl.xticks((1,2,4,8,16,32,64,128,256,512,1024,2048))
mpl.yticks((10, pow(10, 0), pow(10, -1), pow(10, -2), pow(10, -3), pow(10, -4), pow(10, -5), pow(10, -6), pow(10, -7), pow(10, -8), pow(10, -9), pow(10, -10)))
mpl.plot(pl, pl1, "ro--")
mpl.plot(pl, pl2, "mo--")
mpl.plot(pl, pl3, "go--")
mpl.plot(pl, pl4, "yo--")
mpl.xscale('log', basex = 2.0)
mpl.yscale('log')
f.close()
mpl.show()

