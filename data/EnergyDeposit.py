import numpy as np
import matplotlib.pyplot as plt

eDep_file_t0 = np.genfromtxt('Edep_nt_NaI_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('Edep_nt_NaI_t1.csv', delimiter=',')

eDep = []
for i in range(len( eDep_file_t0 )):
        eDep.append( eDep_file_t0[i] )

print( eDep )
for i in range(len( eDep_file_t1 )):
        eDep.append( eDep_file_t1[i] )

plt.hist(eDep, bins=50)
plt.show()