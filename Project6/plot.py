import matplotlib.pyplot as plt

x,y = [], []
cycle = []

with open('input.dat') as f:
    for l in f:
        row = l.split()
        x.append(int(row[0]))
        y.append(int(row[1]))

with open('cycle.dat') as f:
    for l in f:
        row = l.split()
        cycle.append(int(row[0]))

plt.plot(x, y, 'ro')

for i in range(len(cycle) - 1):
    x1 = x[cycle[i]]
    y1 = y[cycle[i]]
    x2 = x[cycle[i+1]]
    y2 = y[cycle[i+1]]
    plt.plot([x1,x2],[y1,y2],'k-')

plt.axis([-110, 110, -110, 110])
plt.show()