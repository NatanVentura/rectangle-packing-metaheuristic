# Define o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -g -O0 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -fsanitize=address

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include

# Nome do executável
TARGET = main

# Lista de arquivos objeto
OBJS = $(SRC_DIR)/DAG.o $(SRC_DIR)/instance.o $(SRC_DIR)/simulated_annealing.o $(SRC_DIR)/main.o

# Regra padrão: compilar tudo
all: $(TARGET)

# Linka os arquivos objeto para criar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para compilar os arquivos fonte em arquivos objeto
$(SRC_DIR)/DAG.o: $(SRC_DIR)/DAG.cpp $(INCLUDE_DIR)/directed_acyclic_graph.hpp $(INCLUDE_DIR)/util.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC_DIR)/instance.o: $(SRC_DIR)/instance.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/util.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC_DIR)/simulated_annealing.o: $(SRC_DIR)/simulated_annealing.cpp $(INCLUDE_DIR)/simulated_annealing.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/directed_acyclic_graph.hpp $(INCLUDE_DIR)/simulated_annealing.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para forçar a recompilação
.PHONY: all clean
