import numpy as np
import matplotlib.pyplot as plt

# GEANT4-files:
eDep_file_t0 = np.genfromtxt('Xe133_beta_spectrum_min10keV_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('Xe133_beta_spectrum_min10keV_t1.csv', delimiter=',')

# From file to array:
eDep = []
for rad in eDep_file_t0:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep.append(a_row)
for rad in eDep_file_t1:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep.append(a_row)

# Only get the beta energy,
# which is the energy in the in the 3rd column
Xe133_beta = []
for rad in eDep:                
        if (rad[3] > 0):       
                Xe133_beta.append(rad[3])


# From Github:
with open('XE133_beta_spectrum.txt') as f:
    values = []

    for line in f:
        rad = line.strip("\n").split(" ")
        en_rad =[]
        for tal in rad:
            en_rad.append( tal )
        values.append(en_rad)

values.pop()    # Remove the last empty line

h = []
for row in values:
    r = []
    for nr in row:
        t = float(nr)           # insted of string
        r.append(t/1000)        # /1000 to get the same units
    h.append(r)

x = []
y = []
for i in range(len(h)):
    x.append(h[i][0])
    y.append(h[i][1])

norm_y = 100000*(np.array(y)/sum(y))    # 100000 = nr of events

# Plot GEANT4 and Github:
plt.plot(x, norm_y,label="true")
plt.hist(Xe133_beta, bins=100, label="GEANT4")
plt.xlim(0, 0.4)
plt.title("Xe133 beta decay, min 10keV")
plt.legend()
plt.savefig("Xe133_beta_spectrum_min10keV.png")
plt.show()