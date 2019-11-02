import sys

import numpy as np
import audiosegment
from matplotlib import pyplot as plt
import time

plt.ion()

def visualize(spect, frequencies, title=""):
    # Visualize the result of calling seg.filter_bank() for any number of filters
    i = 0
    for freq, (index, row) in zip(frequencies[::-1], enumerate(spect[::-1, :])):
        plt.subplot(spect.shape[0], 1, index + 1)
        if i == 0:
            plt.title(title)
            i += 1
        plt.ylabel("{0:.0f}".format(freq))
        plt.plot(row)
    plt.show()

video_source = sys.argv[1]
sound = audiosegment.from_file(video_source).resample(sample_rate_Hz=24000, sample_width=2, channels=1)
spec, frequencies = sound.filter_bank(nfilters=5)
#  visualize(spec, frequencies)

offset = 1000
for i in range(0, len(sound)-offset, offset):
    hist_bins, hist_vals = sound[i:i+offset].fft()
    hist_bins, hist_vals = hist_bins[400:1200], hist_vals[400:1200]
    hist_vals_real_normed = np.abs(hist_vals) / len(hist_vals)
    print(hist_vals_real_normed[0:10])
    plt.plot(hist_bins, hist_vals_real_normed)
    plt.xlabel("Hz")
    plt.ylabel("dB")
    plt.draw()
    plt.pause(1)
    #  plt.cla()

time.sleep(10)
