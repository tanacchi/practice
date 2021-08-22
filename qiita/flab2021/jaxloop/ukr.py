import jax.numpy as jnp
from jax.config import config
import numpy as np
import jax
from tqdm import tqdm
import time


config.update("jax_enable_x64", True)


class UKR(object):
    def __init__(self, latent_dim, eta, sigma, scale, clipping=(-1, +1)):
        self.L = latent_dim
        self.eta = eta
        self.sigma = sigma
        self.scale = scale
        self.clipping = clipping

    def fit(self, X, num_epoch=50, seed=0, f_resolution=10):
        N, D = X.shape
        np.random.seed(seed)
        Z = np.random.uniform(low=-0.01, high=0.01, size=(N, self.L))
        X, Z = jnp.array(X), jnp.array(Z)

        history = dict(
            E=np.zeros((num_epoch,)),
            Y=np.zeros((num_epoch, N, D)),
            Z=np.zeros((num_epoch, N, self.L)))
        Zs = []

        begin = time.time()
        for epoch in range(num_epoch):
            Z = estimate_z(X, Z, self.sigma, self.eta, self.clipping)
            Zs.append(Z)
        end = time.time()
        print("time:", end - begin)

        for epoch in tqdm(range(num_epoch)):
            Y = estimate_f(Zs[epoch], Zs[epoch], X, self.sigma)
            history['E'][epoch] = np.sum((Y - X)**2) / N
            history['Y'][epoch] = np.array(Y)
        history['Z'] = np.array(Zs)
        return history


@jax.jit
def estimate_f(Z1, Z2, X, sigma):
    dists = ((Z1[:, None, :] - Z2[None, :, :])**2).sum(axis=2)
    R = jnp.exp(-0.5 * dists / sigma**2)
    R /= R.sum(axis=1, keepdims=True)
    return R @ X


@jax.jit
def estimate_z(X, Z, sigma, eta, clipping):
    dZ = jax.grad(lambda z: obf(X, z, sigma))(Z)
    Z -= eta * dZ
    Z = jnp.clip(Z, clipping[0], clipping[1])
    return Z


@jax.jit
def obf(X, Z, sigma):
    return jnp.sum((estimate_f(Z, Z, X, sigma) - X)**2) / X.shape[0]


if __name__ == '__main__':
    import data
    from visualizer import visualize_history


    X = data.gen_saddle_shape(num_samples=1000, random_seed=0, noise_scale=0.05)
    ukr = UKR(latent_dim=2, eta=8, sigma=0.2, scale=1e-3, clipping=(-1, 1))
    history = ukr.fit(X, num_epoch=10000)
    visualize_history(X, history['Y'], history['Z'], save_gif=False)
