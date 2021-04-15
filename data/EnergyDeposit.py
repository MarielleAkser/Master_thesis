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

coincidence = []

for rad in eDep:
        for i in range(len(rad)):
                if (rad[i] != 0 and rad[i+1] != 0):
                        coincidence.append(rad)
                break

print(coincidence)
c = np.array(coincidence)

plt.hist2d(c[:,1], c[:,0], bins=50, density=False, cmap="Greys")
plt.ylabel(r'$E_\gamma$')
plt.xlabel(r'$E_\beta$')
plt.colorbar()
plt.show()

# 2D histogrsm plot
# plt.hist2d(m[:,0], m[:,1], bins=50, density=False, cmap="Reds")
# plt.xlabel("NaI detector")
# plt.ylabel("Beta detactor")
# plt.colorbar()
# plt.show()