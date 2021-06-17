import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from numpy.lib.function_base import average

# Opens the corresponding files, Run5 has 10 000 events
eDep_file_t0 = np.genfromtxt('xe135_tripleRun1_t0.csv', delimiter=',')
eDep_file_t1 = np.genfromtxt('xe135_tripleRun1_t1.csv', delimiter=',')

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
nr_events = 0
nr_coinc = 0
nr_array = []
# Create a triple coincidence arrays
coincidence = []
# Creating a beta_3 array for the beta energy when all 3 particle is deposit energy > 0
beta_3 = []
for rad in eDep:
        nr_events += 1
        """gamma:[1] = 31.6 +- 5 keV --> 0.0266 & 0.0366 MeV,
        conversion electron:[7] = 214 +- 5 keV --> 0.209 & 0.219 MeV,
        beta:[11] > 0"""
        a_row = []
        t = []
        # if ( (rad[1] > 0) and (rad[7] > 0) and (rad[11] > 0) ):
        if ( (0.0266 <= rad[1] <= 0.0366) and (0.209 <= rad[7] <= 0.219) and (rad[11] > 0) ):
                a_row.append(rad[1])
                a_row.append(rad[7])
                a_row.append(rad[11])
                coincidence.append(a_row)

                nr_coinc += 1
        t.append(nr_events)
        t.append(nr_coinc)
        nr_array.append(t)

        if ( (rad[1] > 0) and (rad[7] > 0) and (rad[11] > 0) ): # All particle gets detected
                beta_3.append(rad[11])


c = np.array(coincidence)

# Getting all the beta, gamma and CE energies:
eDep_beta = []
eDep_gamma = []
eDep_CE = []
for rad in eDep:
        if (0.0266 <= rad[1] <= 0.0366):
                eDep_gamma.append(rad[1])
        if (0.209 <= rad[7] <= 0.219):
                eDep_CE.append(rad[7])
        if (rad[11] > 0):
                eDep_beta.append(rad[11])

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


print("......................... GAMMA ...............................")
print("Total nr of gamma particles detected: ", len(eDep_gamma), 
        "\n which gives the %: ", len(eDep_gamma) / len(eDep))
print("Nr of gamma particles detected in coincidence: ", len(c[:,0]), 
        "\n which gives the %: ", len(c[:,0]) / len(eDep))
print("% that are detected that are in coincidence ", len(c[:,0]) / len(eDep_gamma)  )
print("...............................................................")

print("-------------------------- BETA --------------------------")
print("Total nr of beta particles detected: ", len(eDep_beta), 
        "\n which gives the %: ", len(eDep_beta) / len(eDep))
print("Nr of beta particles detected in coincidence: ", len(c[:,2]), 
        "\n which gives the %: ", len(c[:,2]) / len(eDep))
print("% that are detected that are in coincidence: ", len(c[:,2]) / len(eDep_beta)  )
print("----------------------------------------------------------")


print("************************** CE ****************************")
print("Total nr of CE particles detected: ", len(eDep_CE), 
        "\n which gives the %: ", len(eDep_CE) / len(eDep))
print("Nr of CE particles detected in coincidence: ", len(c[:,1]), 
        "\n which gives the %: ", len(c[:,1]) / len(eDep))
print("% that are detected that are in coincidence: ", len(c[:,1]) / len(eDep_CE)  )
print("**********************************************************")

# print(coincidence) # [[1,2,3],[4,5,6], ] skriver ut alla rader

# print(c)        #[[1 2 3 ] Skriver bara ut tre i början och dom tre sista
                #[4 5 6]]

coin_procent = (len(c) / len(eDep)) * 100
print("% of coincidence for tripleRun1 xe135:", coin_procent )

p = []
for i in range(len(nr_array)):
        p.append( (nr_array[i][1] / nr_array[i][0]) * 100  )          # 'nr of coinc' / 'nr of events'

print("with the standard deviation: ", np.std(p) )

####################################################
# Number of events that is needed util it converges:
#---------------------------------------------------
# std = [1]
# everyNth = 1000
# for i in range(len(p)):
#         if ( i > 0 and i%everyNth == 0):
#                 std.append( np.std( p[0:i] ) )
# x = np.arange(1,len(nr_array)+1, 1)

# xPlot = x[0::everyNth]
# pPlot = p[0::everyNth]

# plt.errorbar(xPlot, pPlot, yerr=std )
# plt.xlabel("Number of events")
# plt.ylabel("% of coincidence")
# plt.title("Events needed to get coincidence rate to converges")
# plt.savefig("plot_converges_tripleRun1_xe135.png")
# plt.show()

# # # Zoomed in:
# plt.errorbar(xPlot, pPlot, yerr=std )
# plt.xlabel("Number of events")
# plt.ylabel("% of coincidence")
# plt.title("Events needed to get coincidence rate to converges")
# plt.xlim(len(eDep)-100001, len(eDep))
# plt.ylim(coin_procent-3*np.std(p), coin_procent+3*np.std(p))
# plt.savefig("plot_convergesZoom_tripleRun1_xe135.png")
# plt.show()
######################################################

######################################################
# 2D coincidence histogram over beta and gamma energy:
# ----------------------------------------------------
# plt.hist2d(c[:,2], c[:,0], bins=50, density=False, cmap="Greys")
# plt.ylabel(r'$E_\gamma$ [MeV]')
# plt.xlabel(r'$E_\beta$ [MeV]')
# plt.title("Coincidence histogram over \n the gamma and beta energies for Xe-135")
# plt.ylim(0, 0.1)
# plt.xlim(0, 0.910)
# plt.colorbar()
# plt.savefig("plot_BetaGammaCoin_tripleRun1_xe135.png")
# plt.show()
######################################################

######################################################
# 2D coincidence histogram over conversion and gamma energy:
# ----------------------------------------------------
# plt.hist2d(c[:,1], c[:,0], bins=50, density=False, cmap="Greys")
# plt.ylabel(r'$E_\gamma$ [MeV]')
# plt.xlabel(r'$E_{CE}$ [MeV]')
# plt.title("Coincidence histogram over \n the gamma and CE energies")
# # plt.ylim(0, 0.1)
# plt.xlim(0, 0.06)
# plt.colorbar()
# plt.show()
# ######################################################

######################################################
# 2D coincidence histogram over beta and CE energy:
# ----------------------------------------------------
# plt.hist2d(c[:,2], c[:,1], bins=50, density=False, cmap="Greys")
# plt.xlabel(r'$E_\beta$ [MeV]')
# plt.ylabel(r'$E_{CE}$ [MeV]')
# plt.title("Coincidence histogram over \n the beta and CE energies")
# plt.ylim(0, 0.05)
# plt.xlim(0, 0.346)
# plt.colorbar()
# plt.show()
######################################################

#######################################################################
# 1D histogram plot over Beta energy together with the 'correct' values
# #--------------------------------------------------------------------
plt.plot(x,y_norm, label="True", color="black")
plt.hist(eDep_beta, bins=360, label="All beta from simulation", color="#4575b4")
plt.hist(beta_3, bins=360, label="Beta when three particles \n\
are detected", color="#d73027")
plt.hist(c[:,2], bins=360, label="From simulation in \n\
triple coincidence", color="#ffffbf")
plt.xlabel("Energy [MeV]")
plt.ylabel("Counts")
plt.title("Energy distribution for the beta particle of Xe-135")
plt.legend()
plt.xlim(0,0.910)
plt.savefig("plot_BetaEnergy_tripleRun1_xe135.png")
plt.show()
#######################################################################

# # ####################################
# 1D histogram plot over CE 
# #-----------------------------------
# print( max(eDep_CE))
# print("min ", min(eDep_CE))
# plt.hist(eDep_CE, bins=100, label="All detected CE")
# plt.hist(c[:,1], bins=100, label="CE in coincidence", histtype="step", color="black")
# plt.legend()
# plt.title("Histogram over the conversion electron for Xe-135")
# plt.xlabel("Energy [MeV]")
# plt.ylabel("Counts")
# plt.xlim(0)
# plt.ylim(0)
# plt.savefig("plot_CEhist_tripleRun1_xe135.png")
# plt.show()
# # ####################################

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
# # ####################################


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