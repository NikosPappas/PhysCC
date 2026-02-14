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

// Helper to print usage
void print_usage() {
    std::cout << "Usage: physcc <input_file> [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --backend <name>   Target backend: cpp, mpi, sycl, cuda, avx2\n";
    std::cout << "  --init <type>      Initialization: zero, gaussian\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string input_file = argv[1];
    std::string backend_type = "cpp"; 
    std::string init_type = "zero";

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--backend" && i + 1 < argc) {
            backend_type = argv[++i];
        } else if (arg == "--init" && i + 1 < argc) {
            init_type = argv[++i];
        }
    }

    // 1. Read Input
    std::ifstream file(input_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << input_file << std::endl;
        return 1;
    }
    
    // Lexer requires wide stream
    std::string source_str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_source = converter.from_bytes(source_str);
    std::wstringstream source_stream(wide_source);

    std::cout << "[PhysCC] Compiling " << input_file << " for " << backend_type << "...\n";

    // 2. Lexer
    Lexer lexer(source_stream);

    // 3. Parser
    Parser parser(lexer);
    auto ast = parser.parse();

    // 4. Create Context & Semantic Analysis
    CompilerContext ctx;           // 🟢 Create the context
    ctx.system = std::move(ast);   // 🟢 Move AST into context

    SemanticPass semantic_pass;
    if (!semantic_pass.run(ctx)) { // 🟢 Pass context, not AST
        std::cerr << "Semantic Error: Physics check failed.\n";
        return 1;
    }

    // 5. Stencil Analysis
    StencilPass stencil_pass;
    stencil_pass.run(ctx);         // 🟢 Pass context
    IntegratorIR ir = ctx.ir;      // 🟢 Extract IR from context
    ir.dt = 0.01; 

    // 6. Code Generation
    BackendIR backend_config;
    backend_config.init_type = init_type;

    std::ofstream out("generated.cpp");
    if (backend_type == "cpp") {
        emitCpp(ir, backend_config, out);
    } 
    else if (backend_type == "mpi") {
        emitMPI(ir, backend_config, out);
    } 
    else if (backend_type == "sycl") {
        emitSycl(ir, backend_config, out);
    }
    else if (backend_type == "cuda") { 
        emitCuda(ir, backend_config, out); 
    }
    else if (backend_type == "avx2") {
        std::cout << "[Codegen] Targeting AVX2 SIMD ...\n";
        emitAVX2(ir, backend_config, out);
    }
    else {
        std::cerr << "Error: Unknown backend '" << backend_type << "'\n";
        return 1;
    }

    std::cout << "✅ Success! Produced generated.cpp\n";
    return 0;
}
