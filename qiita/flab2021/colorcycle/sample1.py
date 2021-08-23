from matplotlib import colors
import numpy as np
import matplotlib as mpl
from matplotlib import pyplot as plt
# from colorsys import hsv_to_rgb


if __name__ == '__main__':
    num_tasks = 30
    num_samples = 1000
    x = np.linspace(-np.pi, np.pi, num_samples)
    Y = np.empty((num_tasks, num_samples))
    for i in range(num_tasks):
        Y[i] = np.sin(x) + 0.1*i

    fig = plt.figure()
    ax = fig.add_subplot(111)

    colors = [ mpl.cm.cool(h) for h in np.linspace(0, 1, 30, endpoint=False) ]
    ax.set_prop_cycle(color=colors)
    for y in Y:
        ax.plot(x, y)
    plt.show()
