import numpy as np
import matplotlib as mpl
from matplotlib import pyplot as plt
from itertools import product
from colorsys import hsv_to_rgb


def make_grid(resolution, domain):
    mesh = np.linspace(domain[0], domain[1], resolution)
    return np.array(list(product(mesh, repeat=2)))


def gen_star_dots(center, radius):
    thetas = (np.linspace(0, 4, 6, endpoint=True) + 0.1) * np.pi
    x = radius * np.cos(thetas) + center[0]
    y = radius * np.sin(thetas) + center[1]
    return np.concatenate([x[:, np.newaxis], y[:, np.newaxis]], axis=1)


if __name__ == '__main__':
    # Making multiple stars (7*7).
    resolution = 7
    grid = make_grid(resolution, domain=(0, 1))
    X = np.empty((resolution**2, 6, 2))
    for i, center in enumerate(grid):
        X[i] = gen_star_dots(center, radius=0.05)

    # Making list of colors (7*7 × RGB).
    colors = [
        hsv_to_rgb(h, 0.8, v) for h, v in make_grid(resolution, domain=(0.3, 1))
    ]

    # Drawing sine stars.
    fig = plt.figure(figsize=(7, 7))
    ax = fig.add_subplot(111)
    ax.set_aspect('equal')
    ax.set_prop_cycle(color=colors)  # Setting color cycle !
    for x in X:
        ax.plot(x[:, 0], x[:, 1], lw=3)
    plt.show()
