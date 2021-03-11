import numpy as np
import matplotlib.pyplot as plt

# The first 3 rows in the file is not included. 
eDep_file = np.genfromtxt('eDep.csv', delimiter=',')

eDep = []
for i in range(len( eDep_file )):
    if eDep_file[i][3] != 0:
        eDep.append( eDep_file[i][3] *1000 )


plt.hist(eDep, bins=250)
plt.title("Histogram over the energy deposit \n in the boxMesh")
plt.xlabel("Energy deposit [keV]")
plt.ylabel("Counts")
plt.ylim(0,25)
plt.savefig("eDep_hist_MeshBox.jpg")
plt.show()