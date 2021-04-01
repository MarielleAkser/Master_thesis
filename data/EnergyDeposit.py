import numpy as np
import matplotlib.pyplot as plt

eDep_file_t0 = np.genfromtxt('Edep_nt_NaI_Beta_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('Edep_nt_NaI_Beta_t1.csv', delimiter=',')

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

m = np.array(eDep)

plt.hist2d(m[:,0], m[:,1], bins=50, density=False, cmap="Reds")
plt.xlabel("NaI detector")
plt.ylabel("Beta detactor")
plt.colorbar()
plt.show()