import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from numpy.lib.function_base import average

# Opens the corresponding files, Run2 1 000 000 events
eDep_file_t0 = np.genfromtxt('xe135_betaRun2_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('xe135_betaRun2_t1.csv', delimiter=',')

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


# To calculate when the number of events converges
antal_events = 0
antal_coinc = 0
procent_coinc = []
# Create a triple coincidence arrays
coincidence = []
all_energy_eDep = []
for rad in eDep:
        antal_events += 1
        """beta:[3]"""
        t = []
        aSum = rad[1] + rad[3] + rad[5] + rad[7] + rad[9] + rad[11]
        if (rad[3] > 0 ):
                coincidence.append(rad[3])
                antal_coinc += 1
        t.append(antal_events)
        t.append(antal_coinc)
        procent_coinc.append(t)

        if (aSum > 0):
                all_energy_eDep.append(aSum)

c = np.array(coincidence)
# Get the correct values for the beta distribution:
with open('XE135_beta_spectrum.txt') as f:
    values = []
    for line in f:
        rad = line.strip("\n").split(" ")
        en_rad =[]
        for tal in rad:
            en_rad.append( tal )
        values.append(en_rad)
values.pop()    # Remove the last empty line
# Create a array with float insted of strings
h = []
for row in values:
    r = []
    for nr in row:
        r.append( float(nr) )       
    h.append(r)

x = []          # energy
y = []          # probability, not normalized
for i in range(len(h)):
    x.append(h[i][0] / 1000 )    # To get the energy in MeV
    y.append(h[i][1])

# Need to normalize y:
y_norm =  (np.array(y) / sum(y) )  * len(eDep)  # len(eDep) = nr of events


print("Total number if particles generated: ", len(eDep) )


print("-------------------------- BETA --------------------------")
print("Total nr of beta particles detected: ", len(c),  
        "\n which gives the %: ", len(c) / len(eDep) )
print("----------------------------------------------------------")


# print(coincidence) # [[1,2,3],[4,5,6], ] skriver ut alla rader

# print(c)        #[[1 2 3 ] Skriver bara ut tre i början och dom tre sista
                #[4 5 6]]

print("% for betaRun2 Xe135:", (len(c) / len(eDep)) * 100 )
print("total energy deposit > 0: ", len(all_energy_eDep))


#######################################################################
# 1D histogram plot over Beta energy together with the 'correct' values
# #--------------------------------------------------------------------
# Plot
plt.plot(x,y_norm, label="True", color="black")
plt.hist(c, bins=330, label="Beta energy in beta cell", density=False ,
        alpha=0.8, color="#1b7837")
plt.hist(all_energy_eDep, bins=330, label="Beta energy from simulation \nin any detector", 
        density=False, histtype='step', facecolor='g', edgecolor="#762a83")
plt.xlabel("Energy [MeV]")
plt.ylabel("Counts")
plt.title("Energy distribution for the beta particle of Xe-135")
plt.legend()
plt.xlim(0,0.910)
plt.savefig("plot_BetaEnergy_betaRun2_xe135.png")
plt.show()
#######################################################################

# # ####################################
# 1D histogram plot over CE 
# #-----------------------------------
# print( max(eDep_CE))
# plt.hist(eDep_CE, bins=100, label="All detected CE")
# plt.hist(c[:,1], bins=100, label="CE in coincidence")
# plt.legend()
# plt.title("Histogram over the conversion electron")
# plt.xlabel("Energy [MeV]")
# plt.ylabel("Counts")
# plt.xlim(0, 0.05)
# plt.ylim(0)
# plt.show()

# ####################################
# 1D histogram plot over gamma
# #-----------------------------------
# print( min(c[:,0]))
# plt.hist(eDep_gamma, bins=100, label="All detected gamma")
# plt.hist(c[:,0], bins=100, label="gamma in coincidence")
# plt.legend()
# plt.title("Histogram over the gamma")
# plt.xlabel("Energy [MeV]")
# plt.ylabel("Counts")
# plt.xlim(0)
# plt.ylim(0)
# plt.show()

##############
# 3D:
# -------------
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')


# x = c[:,0]
# y = c[:,1]
# z = c[:,2]
# k = np.random.standard_normal(len(c[:,0]))

# img = ax.scatter(x, y, z, c=k, cmap="Greys")
# fig.colorbar(img)
# ax.set_xlabel('gamma')
# ax.set_ylabel('CE')
# ax.set_zlabel('Beta')
# plt.show()