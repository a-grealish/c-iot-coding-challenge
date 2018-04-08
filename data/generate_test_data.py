import random as rd
import numpy as np
import matplotlib.pyplot as plt

ittrs = 100000
on_count = 0
lines = 0

values = []

with open("test_file.txt", "w") as f:
    for i in range(0, rd.randrange(0, ittrs, 1)):
        on = round(rd.random())
        for j in range(0, rd.randrange(10, 200, 1)):  
            on_count += on
            lines += 1

            value = on + (rd.random()/10)

            values.append(value)

            f.write(str(value)[::-1]+'\n')


print (on_count / lines)

plt.plot(values)
plt.show()

# Do k-means clustering on the values 
def k_means(values, ks=2):
    means = []

    # Forgy Init - Choose random point from the value array
    for k in range(0, ks):
        means.append(values[rd.randrange(0, lines, 1)])

    print ("Init means: ", means)

    prev_means = []

    k_sums = [0 for x in range(0, ks)]
    k_count = [0 for x in range(0, ks)]

    i = 0

    while (1):

        prev_means = means[:]

        # For each val assign to a k
        for val in values:
            closest_k = 0
            closest_k_dist = abs(val - means[0])
            for k in range(1, ks):
                if abs(val - means[k]) < closest_k_dist:
                    closest_k_dist = abs(val - means[k])
                    closest_k = k

            # Add the value to the sum for that closest k and increment the count
            k_sums[closest_k] += val
            k_count[closest_k] += 1

        # Calculate the new means
        for k in range(0, ks):
            # print k_sums[k], k_count[k]
            if k_count[k] != 0:
                means[k] = k_sums[k] / k_count[k]
        
        # Check if the means have converged
        converged = True
        for k in range(0, ks):
            if abs(prev_means[k] - means[k]) > 0.00001:
                converged = False
        if converged:
            print("Means converged")
            break

        # Max 50 itterations
        i += 1
        if (i > 20):
            print("Reached ittr limit")
            break

    print ("Final means: ", means)

# k_means(values)