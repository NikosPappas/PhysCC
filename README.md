# PhysCC: A Domain-Specific Compiler for Stencil-Based Physics

![Quantum Tunneling](https://your-image-link-here.png) 
*Visualizing a Gaussian wave packet tunneling through a potential barrier, simulated via PhysCC-generated AVX2 code.*

## 🚀 Overview
**PhysCC** is a high-performance Domain-Specific Language (DSL) and compiler designed to translate abstract mathematical equations into hardware-optimized C++ code. By decoupling physical semantics from hardware implementation, PhysCC enables researchers to execute complex simulations (Wave Equation, Schrödinger Equation) at near-peak hardware throughput.

### Key Features
* **Unicode-Aware Lexer:** Native support for symbols like $\nabla^2$ and $\hbar$.
* **Complex-Regime Optimization:** Automatic **Structure of Arrays (SoA)** transformation for de-interleaved SIMD execution.
* **Hybrid-Architecture Awareness:** Thread affinity management optimized for Intel P-cores/E-cores.
* **Multi-Backend Support:** Generates optimized code for **AVX2 (SIMD)**, **MPI (Distributed)**, and **SYCL (GPU)**.

---

## 📊 Performance Benchmarks
Tested on Intel Core i5-1235U (10 Cores, 12 Threads).

| Regime | Implementation | Throughput (GUPS) | Bottleneck |
| :--- | :--- | :--- | :--- |
| Classical Wave | AVX2 (256-bit) | 1.467 | Compute-Bound |
| Quantum (TDSE) | De-interleaved SoA | 0.559 | Cache/Memory Bandwidth |




---

## 🛠️ Usage Workflow

### 1. Build the Compiler
```bash
make clean && make
./physcc --help   
