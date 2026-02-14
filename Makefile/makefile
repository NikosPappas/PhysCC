CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O3

# All source files
SRC = src/lexer/lexer.cpp \
      src/parser/parser.cpp \
      src/parser/ast_printer.cpp \
      src/passes/parse_pass.cpp \
      src/passes/semantic_pass.cpp \
      src/passes/stencil_pass.cpp \
      src/passes/codegen_pass.cpp \
      src/codegen/codegen.cpp \
      src/codegen/codegen_python.cpp \
      src/codegen/codegen_mpi.cpp \
      src/codegen/codegen_cuda.cpp \
      src/codegen/codegen_sycl.cpp \
      src/codegen/codegen_avx2.cpp \
      src/main.cpp

# The output binary
TARGET = physcc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) generated.cpp simulation.py simulation_mpi.cpp simulation.cu simulation_sycl.cpp data.csv reaction_sim

test: $(TARGET)
	./$(TARGET) tests/reaction_diffusion.phys --backend python
	python3 simulation.py
