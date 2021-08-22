import jax.numpy as jnp
from jax.config import config
import numpy as np
from jax import grad
from tqdm import tqdm


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

        for epoch in tqdm(range(num_epoch)):
            Y = estimate_f(Z, Z, X, self.sigma)
            Z = estimate_z(X, Z, self.sigma, self.eta, self.clipping)

            history['E'][epoch] = np.sum((Y - X)**2) / N
            history['Y'][epoch] = np.array(Y)
            history['Z'][epoch] = np.array(Z)
        return history


def estimate_f(Z1, Z2, X, sigma):
    dists = ((Z1[:, None, :] - Z2[None, :, :])**2).sum(axis=2)
    R = jnp.exp(-0.5 * dists / sigma**2)
    R /= R.sum(axis=1, keepdims=True)
    return R @ X


def estimate_z(X, Z, sigma, eta, clipping):
    dZ = grad(lambda z: obf(X, z, sigma))(Z)
    Z -= eta * dZ
    Z = jnp.clip(Z, clipping[0], clipping[1])
    return Z


def obf(X, Z, sigma):
    return jnp.sum((estimate_f(Z, Z, X, sigma) - X)**2) / X.shape[0]


if __name__ == '__main__':
    import data
    from visualizer import visualize_history


    X = data.gen_saddle_shape(num_samples=200, random_seed=0, noise_scale=0.05)
    # X = data.gen_2d_sin_curve(100, random_seed=0, noise_scale=0.01)
    ukr = UKR(latent_dim=2, eta=8, sigma=0.2, scale=1e-3, clipping=(-1, 1))
    history = ukr.fit(X, num_epoch=300)
    visualize_history(X, history['Y'], history['Z'], save_gif=False)
