import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load the data
data = pd.read_csv('data_final.csv', header=None).values

# Plot
plt.figure(figsize=(10, 8))
plt.imshow(data, cmap='RdBu', extent=[-1, 1, -1, 1])
plt.colorbar(label='Amplitude (u)')
plt.title('Final State of Gaussian Ripple (SYCL + Iris Xe)')
plt.show()
