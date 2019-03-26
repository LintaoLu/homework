import numpy as np
import matplotlib.pyplot as plt

with open('network-test-latency.txt') as f:
    lines = f.readlines()
    x = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

x, y = zip(*sorted(zip(x, y)))


fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("DSN Ping")    
ax1.set_ylabel('ms')

ax1.plot(x,y, c='r', label='speed')

leg = ax1.legend()

plt.gca().invert_yaxis()
plt.xticks(rotation=45)

plt.gcf().subplots_adjust(bottom=0.25)

plt.show()
