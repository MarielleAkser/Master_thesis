import numpy as np
import matplotlib.pyplot as plt

eDep_file_t0 = np.genfromtxt('Xe133_beta_spectrum_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('Xe133_beta_spectrum_t1.csv', delimiter=',')

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

Xe133_beta = []
for rad in eDep:
    if (rad[3] > 0):
        Xe133_beta.append(rad[3])



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
        r.append(t/1000)
    h.append(r)

x = []
y = []
for i in range(len(h)):
    x.append(h[i][0])
    y.append(h[i][1])
print(sum(y))

plt.plot(x, 100000*(np.array(y)/sum(y)), label="true" )
plt.hist(Xe133_beta, bins=100, label="GEANT4")
plt.xlim(0, 0.4)
plt.title("Xe133 beta decay, min 0keV")
plt.legend()
plt.savefig("Xe133_beta_spectrum_min0keV.png")
plt.show()