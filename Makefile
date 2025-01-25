# Define o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -g -O0 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -fsanitize=address

# Diretórios
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
DATA_DIR = data

# Nome do executável
TARGET = main

# Lista de arquivos objeto
OBJS = $(BIN_DIR)/DAG.o $(BIN_DIR)/instance.o $(BIN_DIR)/simulated_annealing.o $(BIN_DIR)/evolutionary_algorithm.o $(BIN_DIR)/main.o

# Arquivo do gerador de dados
DATA_GEN_SRC = $(SRC_DIR)/data_generator.cpp
DATA_GEN_TARGET = $(BIN_DIR)/data_generator.out

# Regra padrão: compilar tudo
all: $(TARGET)

# Linka os arquivos objeto para criar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar o gerador de dados
$(DATA_GEN_TARGET): $(DATA_GEN_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(DATA_GEN_TARGET) $(DATA_GEN_SRC)

# Regra para executar o gerador de dados
data: $(DATA_GEN_TARGET)
	@mkdir -p $(DATA_DIR)
	./$(DATA_GEN_TARGET)

# Regras para compilar os arquivos fonte em arquivos objeto
$(BIN_DIR)/DAG.o: $(SRC_DIR)/DAG.cpp $(INCLUDE_DIR)/directed_acyclic_graph.hpp $(INCLUDE_DIR)/util.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/instance.o: $(SRC_DIR)/instance.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/util.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/simulated_annealing.o: $(SRC_DIR)/simulated_annealing.cpp $(INCLUDE_DIR)/simulated_annealing.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/evolutionary_algorithm.o: $(SRC_DIR)/evolutionary_algorithm.cpp $(INCLUDE_DIR)/evolutionary_algorithm.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/directed_acyclic_graph.hpp $(INCLUDE_DIR)/simulated_annealing.hpp $(INCLUDE_DIR)/evolutionary_algorithm.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET) $(DATA_GEN_TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para forçar a recompilação
.PHONY: all clean run data
