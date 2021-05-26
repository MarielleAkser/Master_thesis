import numpy as np
import matplotlib.pyplot as plt

#########
# RUN 1 #
#########

# Opens the corresponding files
eDep_file_t0_Run1 = np.genfromtxt('xe133_tripleRun1_t0.csv', delimiter=',')
eDep_file_t1_Run1 = np.genfromtxt('xe133_tripleRun1_t1.csv', delimiter=',')

# From files to array:
eDep_Run1 = []
for rad in eDep_file_t0_Run1:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep_Run1.append(a_row)
for rad in eDep_file_t1_Run1:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep_Run1.append(a_row)

# Create a triple coincidence arrays
coincidence_Run1 = []
for rad in eDep_Run1:
        """gamma:[1], conversion electron:[7] & beta:[11]"""
        a_row = ()
        if (rad[1] != 0 and rad[7] != 0 and rad[11] != 0):
                a_row = ( rad[1], rad[7], rad[11] )
                coincidence_Run1.append(a_row)


# print(coincidence)
c_Run1 = np.array(coincidence_Run1)


#########
# RUN 2 # WHICH IS THE SAME AS RUN 1
#########

#########
# RUN 3 # WHICH IS ALSO THE SAME AS RUN 1
#########

#########
# RUN 4 # 
#########

# Opens the corresponding files
eDep_file_t0_Run4 = np.genfromtxt('xe133_tripleRun4_t0.csv', delimiter=',')
eDep_file_t1_Run4 = np.genfromtxt('xe133_tripleRun4_t1.csv', delimiter=',')

# From files to array:
eDep_Run4 = []
for rad in eDep_file_t0_Run4:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep_Run4.append(a_row)
for rad in eDep_file_t1_Run4:
        a_row = []
        for tal in rad:
                a_row.append(tal)
        eDep_Run4.append(a_row)

# Create a triple coincidence arrays
coincidence_Run4 = []
for rad in eDep_Run4:
        """gamma:[1], conversion electron:[7] & beta:[11]"""
        a_row = ()
        if (rad[1] != 0 and rad[7] != 0 and rad[11] != 0):
               a_row = ( rad[1], rad[7], rad[11] )
               coincidence_Run4.append(a_row)

c1 = set( coincidence_Run1 )
c4 = set( coincidence_Run4 )
print( "In Run1 and Run4 there are \n" , len( c1 & c4 ), " nr of rows that are exactly the same:")

