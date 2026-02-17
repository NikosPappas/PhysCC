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
import subprocess
import time
import os

# The physics file to optimize
source_file = "tests/reaction_diffusion.phys"
binary = "./reaction_sim"

# Tile sizes to test
tile_sizes = [16, 32, 64, 128, 256, 512]
results = {}

print(f"🚀 Starting Auto-Tuning for {source_file}...")
print("-" * 45)
print(f"{'Configuration':<25} | {'Time (s)':<15}")
print("-" * 45)

# 1. Baseline (No Tiling)
subprocess.run(["./physcc", source_file, "--backend", "cpp"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
subprocess.run(["g++", "generated.cpp", "-o", "reaction_sim", "-O3", "-fopenmp"], stdout=subprocess.DEVNULL)

start_time = time.time()
subprocess.run([binary], stdout=subprocess.DEVNULL)
baseline_time = time.time() - start_time
print(f"{'Baseline (Standard)':<25} | {baseline_time:.4f} s")

# 2. Test Tile Sizes
for size in tile_sizes:
    # Compile with tiling flag
    subprocess.run(["./physcc", source_file, "--backend", "cpp", "--opt-tile", str(size)], stdout=subprocess.DEVNULL)
    
    # Compile the generated C++ code
    subprocess.run(["g++", "generated.cpp", "-o", "reaction_sim", "-O3", "-fopenmp"], stdout=subprocess.DEVNULL)
    
    # Run Benchmark
    start_time = time.time()
    subprocess.run([binary], stdout=subprocess.DEVNULL)
    duration = time.time() - start_time
    
    results[size] = duration
    print(f"{f'Tiled (Size {size})':<25} | {duration:.4f} s")

# 3. Find Winner
best_size = min(results, key=results.get)
best_time = results[best_size]
speedup = baseline_time / best_time

print("-" * 45)
if best_time < baseline_time:
    print(f"🏆 Best Configuration: Tile Size {best_size}")
    print(f"⚡ Speedup vs Baseline: {speedup:.2f}x")
else:
    print("ℹ️  Baseline was faster (Dataset might be too small for tiling)")
    
