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
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import sys

# Check if data exists
try:
    data = []
    with open('data.csv', 'r') as f:
        reader = csv.reader(f, delimiter=' ')
        for row in reader:
            if row: 
                # Parse floats, ignore empty strings from trailing spaces
                data.append([float(x) for x in row if x])
except FileNotFoundError:
    print("Error: 'data.csv' not found. Run a simulation first!")
    sys.exit(1)

if not data:
    print("Error: 'data.csv' is empty.")
    sys.exit(1)

# Set up the plot
fig, ax = plt.subplots()
ax.set_title("Physics Simulation Output")
ax.set_xlabel("Grid Point (x)")
ax.set_ylabel("Amplitude (u)")
ax.set_ylim(-1.5, 1.5)  # Range covers waves and heat
ax.grid(True)

line, = ax.plot(data[0], color='blue', linewidth=2)

def update(frame):
    line.set_ydata(data[frame])
    return line,

# Animate
ani = animation.FuncAnimation(fig, update, frames=len(data), interval=50, blit=True)
plt.show()
