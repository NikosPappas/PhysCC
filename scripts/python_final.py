#/*
# * PhysCC - Domain-Specific Compiler for Physics Simulations
# * Copyright (C) 2026  Nikos Pappas
# * * This program is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# * GNU General Public License for more details.
# */
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
