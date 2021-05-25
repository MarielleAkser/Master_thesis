
import numpy as np
import matplotlib.pyplot as plt
from scipy.constants import e, c, hbar, alpha, m_e
from scipy.integrate import quad
import cmath
import math
import scipy as sp

# File from Github:
with open('XE133_beta_spectrum.txt') as f:
    values = []

    for line in f:
        rad = line.strip("\n").split(" ")
        en_rad =[]
        for tal in rad:
            en_rad.append( tal )
        values.append(en_rad)

values.pop()    # Remove the last empty line

# To get float numbers instead of strings
h = []
for row in values:
    r = []
    for nr in row:
        t = float(nr)
        r.append(t)
    h.append(r)

# Separate into two arrays
x = []  
y = []  
for i in range(len(h)):
    x.append(h[i][0])
    y.append(h[i][1])

x_string = []   # Energy
y_string = []   # Probability
for i in range(len(x)):
    x_string.append( str( x[i] / 1000 ) )    # / 1000 to get energy in MeV
    y_string.append( str(y[i]) )
    
# Copy the text from the 'Xe133_macrofile.txt' 
# to a microfile to get the correct histogram
fil = open('Xe133_macrofile.txt', 'w')
for i in range(len(x_string)):
    L = ["/gps/hist/point ", x_string[i], " ", y_string[i], "\n"]
    fil.writelines(L)
fil.close()

