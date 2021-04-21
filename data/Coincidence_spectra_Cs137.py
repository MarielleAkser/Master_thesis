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

ej_c = np.array(eDep)

coincidence = []
for rad in eDep:
        for i in range(len(rad)):
                if (rad[i] != 0 and rad[i+1] != 0):
                        coincidence.append(rad)
                break

c = np.array(coincidence)

plt.hist2d(c[:,1], c[:,0], bins=50, density=False, cmap="Greys")
plt.ylabel(r'$E_\gamma$' "  [MeV]")
plt.xlabel(r'$E_\beta$' "  [MeV]")
plt.title(r'$\beta-\gamma$'" coincidence spectra for "r'$^{137}Cs$')
plt.xlim(0, 0.7)
plt.ylim(0, 0.7)
plt.colorbar()
plt.savefig("Coin_beta_gamma_Cs137.png")
plt.show()