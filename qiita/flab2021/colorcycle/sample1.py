import numpy as np
import matplotlib as mpl
from matplotlib import pyplot as plt


if __name__ == '__main__':
    # Making multiple sine curves.
    num_tasks = 30
    num_samples = 1000
    x = np.linspace(-np.pi, np.pi, num_samples)
    Y = np.empty((num_tasks, num_samples))
    for i in range(num_tasks):
        Y[i] = np.sin(x) + 0.1*i

    # Making list of colors.
    colors = [ mpl.cm.cool(i) for i in np.linspace(0, 1, num_tasks, endpoint=False) ]

    # Drawing sine curvies.
    fig = plt.figure(figsize=(7, 7))
    ax = fig.add_subplot(111)
    ax.set_aspect('equal')

    ax.set_prop_cycle(color=colors)  # Setting color cycle !
    for y in Y:
        ax.plot(x, y)
    plt.show()
