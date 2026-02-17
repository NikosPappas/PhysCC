/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  Nikos Pappas
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "compiler/context.hpp"
#include "passes/semantic_pass.hpp"
#include "passes/stencil_pass.hpp"
#include "codegen/codegen.hpp"

void print_usage() {
    std::cout << "PhysCC: Domain-Specific Compiler for Physics Simulations\n";
    std::cout << "Usage: ./physcc [options] <input_file.phys>\n\n";
    std::cout << "Options:\n";
    std::cout << "  --help            Show this help message\n";
    std::cout << "  --backend <type>  Specify target: avx2, mpi, cuda, sycl, cpp (default)\n";
    std::cout << "  --init <type>     Initial state: zero (default), gaussian, random\n";
    std::cout << "  -o <file>         Output filename (default: generated.cpp)\n";
    std::cout << "\nExample:\n";
    std::cout << "  ./physcc --backend avx2 -o wave_packet.cpp tests/quantum.phys\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string input_file = "";
    std::string output_file = "generated.cpp";
    std::string backend_type = "cpp"; 
    std::string init_type = "zero";

    // --- 1. Argument Parsing ---
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            print_usage();
            return 0;
        } else if (arg == "--backend" && i + 1 < argc) {
            backend_type = argv[++i];
        } else if (arg == "--init" && i + 1 < argc) {
            init_type = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            output_file = argv[++i];
        } else {
            input_file = arg;
        }
    }

    if (input_file.empty()) {
        std::cerr << "Error: No input file specified.\n";
        return 1;
    }

    // --- 2. Input Ingest ---
    std::ifstream file(input_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << input_file << std::endl;
        return 1;
    }
    
    std::string source_str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_source = converter.from_bytes(source_str);
    std::wstringstream source_stream(wide_source);

    std::cout << "--------------------------------------------------\n";
    std::cout << " ⚛️  PhysCC Compiler\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "[Target]  " << backend_type << "\n";
    std::cout << "[Source]  " << input_file << "\n";

    // --- 3. Frontend & Analysis ---
    Lexer lexer(source_stream);
    Parser parser(lexer);
    auto ast = parser.parse();

    CompilerContext ctx;
    ctx.system = std::move(ast);

    SemanticPass semantic_pass;
    if (!semantic_pass.run(ctx)) {
        std::cerr << "❌ Semantic Error: Physics validation failed.\n";
        return 1;
    }

    StencilPass stencil_pass;
    stencil_pass.run(ctx);
    IntegratorIR ir = ctx.ir;
    ir.dt = 0.01; 

    // --- 4. Backend-Specific Codegen & Build Instructions ---
    BackendIR backend_config;
    backend_config.init_type = init_type;
    std::ofstream out(output_file);

    if (backend_type == "cpp") {
        std::cout << "[Codegen] Emitting Serial C++/OpenMP...\n";
        emitCpp(ir, backend_config, out);
        std::cout << "\n🚀 NEXT STEP:\n   g++ -O3 -fopenmp " << output_file << " -o sim_engine\n";
    } 
    else if (backend_type == "avx2") {
        std::cout << "[Codegen] Emitting Intel AVX2 SIMD...\n";
        emitAVX2(ir, backend_config, out);
        std::cout << "\n🚀 NEXT STEP:\n   g++ -O3 -mavx2 -march=native -fopenmp " << output_file << " -o sim_engine\n";
    }
    else if (backend_type == "mpi") {
        std::cout << "[Codegen] Emitting Distributed MPI...\n";
        emitMPI(ir, backend_config, out);
        std::cout << "\n🚀 NEXT STEP:\n   mpicxx -O3 " << output_file << " -o sim_engine\n";
        std::cout << "   mpirun -np 4 ./sim_engine\n";
    } 
    else if (backend_type == "sycl") {
        std::cout << "[Codegen] Emitting Intel oneAPI SYCL...\n";
        emitSycl(ir, backend_config, out);
        std::cout << "\n🚀 NEXT STEP:\n   icpx -fsycl " << output_file << " -o sim_engine\n";
    }
    else if (backend_type == "cuda") { 
        std::cout << "[Codegen] Emitting NVIDIA CUDA...\n";
        emitCuda(ir, backend_config, out); 
        std::cout << "\n🚀 NEXT STEP:\n   nvcc -O3 " << output_file << " -o sim_engine\n";
    }
    else {
        std::cerr << "❌ Error: Unknown backend '" << backend_type << "'\n";
        return 1;
    }

    std::cout << "\n✅ Compilation Successful. Output: " << output_file << "\n";
    return 0;
}
