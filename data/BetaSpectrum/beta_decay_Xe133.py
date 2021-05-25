
import numpy as np
import matplotlib.pyplot as plt
from scipy.constants import e, c, hbar, alpha, m_e
from scipy.integrate import quad
import cmath
import math
import scipy as sp


with open('XE133_beta_spectrum.txt') as f:
    values = []

    for line in f:
        rad = line.strip("\n").split(" ")
        en_rad =[]
        for tal in rad:
            en_rad.append( tal )
        values.append(en_rad)

values.pop()


h = []
for row in values:
    r = []
    for nr in row:
        t = float(nr)
        r.append(t)
    h.append(r)

x = []
y = []
for i in range(len(h)):
    x.append(h[i][0])
    y.append(h[i][1])
print(sum(y))
plt.plot(x, 100000*(np.array(y)/sum(y)) )
plt.xlim(0,400)
plt.ylim(0)
plt.show()
