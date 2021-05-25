import numpy as np
import matplotlib.pyplot as plt

# Opens the corresponding files
eDep_file_t0 = np.genfromtxt('small_test_xe133_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('small_test_xe133_t1.csv', delimiter=',')

# From files to array:
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

# Create a triple coincidence arrays
coincidence = []
for rad in eDep:
        """gamma:[1], conversion electron:[7] & beta:[11]"""
        a_row = []
        if (rad[1] != 0 and rad[7] != 0 and rad[11] != 0):
                a_row.append(rad[1])
                a_row.append(rad[7])
                a_row.append(rad[11])
                coincidence.append(a_row)


# print(coincidence)
c = np.array(coincidence)

print(len(c))
# print("1: ", min(c[:,1]) , max( c[:,1]))
# print("2: ", min(c[:,2]) , max( c[:,2]))


# plt.hist2d(c[:,2], c[:,0], bins=50, density=False, cmap="Greys")
# plt.ylabel(r'$E_\gamma$')
# plt.xlabel(r'$E_\beta$')
# plt.ylim(0, 0.1)
# plt.xlim(0, 0.346)
# plt.colorbar()
# plt.show()

# 1D histogram plot
plt.hist(c[:,2], bins=50)
# plt.ylim(0, 0.1)
plt.xlim(0, 0.346)
plt.show()