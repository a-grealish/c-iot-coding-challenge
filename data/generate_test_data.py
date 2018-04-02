import random as rd
import numpy as np
import matplotlib.pyplot as plt

ittrs = 1000000
on_count = 0
lines = 0

values = []

with open("test_file.txt", "w") as f:
    for i in range(0, rd.randrange(0, ittrs, 1)):
        on = round(rd.random())
        for j in range(0, rd.randrange(10, 200, 1)):  
            on_count += on
            lines += 1

            value = on + (-0.5 + rd.random()/10)

            values.append(value)

            f.write(str(value)[::-1]+'\n')


print (on_count / lines)

# plt.plot(values)
# plt.show()