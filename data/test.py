
import numpy as np

c1 = [(1,2,3), 
    (4,5,7),
    (7,8,9)]

c2 = [(1,2,3) ,
    (4,5,6), 
    (7,8,9)]

counter = 0

a1 = np.array(c1)
a2 = np.array(c2)

set1 = set(c1)
set2 = set(c2)

print (len( set1 & set2 ) )


# for i in range(len(c1)):
#     # print("i=",i)
#     for j in range(len(c2)):
#         # print("j=",j)
#         if ( c1[i][0] == c2[j][0] and c1[i][1] == c2[j][1] and c1[i][2] == c2[j][2] ):
#             print(c1[i][0])
#             print(c2[j][0])
#             print("---")

#             print(c1[i][1])
#             print(c2[j][1])
#             print("---")

#             print(c1[i][2])
#             print(c2[j][2])
#             counter += 1
#             break
#     print("***************** Counter : ", counter, "**************************")


print(counter)

# print(c1[2][1])
# print(i)