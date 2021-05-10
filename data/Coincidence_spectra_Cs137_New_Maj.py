import numpy as np
import matplotlib.pyplot as plt

eDep_file_t0 = np.genfromtxt('Edep_and_Particle_nt_detector_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('Edep_and_Particle_nt_detector_t1.csv', delimiter=',')

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

# print(ej_c)

coincidence = []
for rad in eDep:
        coin_rad = []
        if ( rad[1] != 0 and rad[3] != 0):
                coin_rad.append(rad[1])
                coin_rad.append(rad[3])

                coincidence.append(coin_rad)
        
# print(coincidence)
c = np.array(coincidence)
# print(c)

plt.hist2d(c[:,1], c[:,0], bins=50, density=False, cmap="Greys")
plt.ylabel(r'$E_\gamma$' "  [MeV]")
plt.xlabel(r'$E_\beta$' "  [MeV]")
plt.title(r'$\beta-\gamma$'" coincidence spectra for "r'$^{137}Cs$')
plt.xlim(0, 0.7)
plt.ylim(0, 0.7)
plt.colorbar()
plt.savefig("Coin_beta_gamma_Cs137_New_Maj.png")
plt.show()