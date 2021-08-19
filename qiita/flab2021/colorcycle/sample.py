import numpy as np
import matplotlib as mpl
from matplotlib import colors, pyplot as plt
from cycler import cycler
from colorsys import hsv_to_rgb


colors = [ hsv_to_rgb(h, 1.0, 0.9) for h in np.linspace(0, 1, 30, endpoint=False) ]
mpl.rcParams['axes.prop_cycle'] = cycler(color=colors)


if __name__ == '__main__':
    num_tasks = 20
    num_samples = 1000
    x = np.linspace(-np.pi, np.pi, num_samples)
    Y = np.empty((num_tasks, num_samples))
    for i in range(num_tasks):
        Y[i] = np.sin(x) + 0.1*i


    for y in Y:
        plt.plot(x, y)
    plt.show()
