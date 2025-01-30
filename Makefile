# Simples é mais sucesso
# o make file tava complicado porque tinha varias mains
all:
	g++ src/DAG.cpp src/evolutionary_algorithm.cpp src/instance.cpp src/process_instances.cpp src/simulated_annealing.cpp -I include -O3 -DNDEBUG

# pra debugar:
# all:
# 	g++ src/*.cpp -I include -g -O0 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -fsanitize=address

# # Define o compilador e as flags de compilação
# CXX = g++ 
# CXXFLAGS = -std=c++17 -Iinclude -g -O0 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -fsanitize=address
# # Quando for rodar de verdade usa:
# # CXXFLAGS = -std=c++17 -Iinclude -O3 -DNDEBUG

# # Diretórios
# SRC_DIR = src
# BIN_DIR = bin
# INCLUDE_DIR = include
# DATA_DIR = data

# # Nome do executável
# TARGET = main

# # Lista de arquivos objeto
# OBJS = $(BIN_DIR)/DAG.o $(BIN_DIR)/instance.o $(BIN_DIR)/simulated_annealing.o $(BIN_DIR)/evolutionary_algorithm.o $(BIN_DIR)/main.o

# # Arquivo do gerador de dados
# DATA_GEN_SRC = $(SRC_DIR)/data_generator.cpp
# DATA_GEN_TARGET = $(BIN_DIR)/data_generator.out

# # Arquivo do processador de instâncias
# PROCESS_SRC = $(SRC_DIR)/process_instances.cpp
# PROCESS_OBJS = $(BIN_DIR)/DAG.o $(BIN_DIR)/instance.o $(BIN_DIR)/simulated_annealing.o $(BIN_DIR)/evolutionary_algorithm.o
# PROCESS_TARGET = $(BIN_DIR)/process_instances.out

# # Arquivo do teste do algoritmo evolutivo
# TEST_SRC = $(SRC_DIR)/test_evolutionary_algorithm.cpp
# TEST_TARGET = $(BIN_DIR)/test_evolutionary_algorithm.out

# Regra padrão: compilar tudo
# all: $(TARGET)

# Linka os arquivos objeto para criar o executável
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar o gerador de dados
# $(DATA_GEN_TARGET): $(DATA_GEN_SRC)
# 	@mkdir -p $(BIN_DIR)
# 	$(CXX) $(CXXFLAGS) -o $(DATA_GEN_TARGET) $(DATA_GEN_SRC)

# Regra para compilar o processador de instâncias
# $(PROCESS_TARGET): $(PROCESS_SRC) $(PROCESS_OBJS)
# 	@mkdir -p $(BIN_DIR)
# 	$(CXX) $(CXXFLAGS) -o $(PROCESS_TARGET) $(PROCESS_SRC) $(PROCESS_OBJS)

# Regra para compilar o teste do algoritmo evolutivo
# $(TEST_TARGET): $(TEST_SRC) $(PROCESS_OBJS)
# 	@mkdir -p $(BIN_DIR)
# 	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(PROCESS_OBJS)

# Regra para executar o gerador de dados
# data: $(DATA_GEN_TARGET)
# 	@mkdir -p $(DATA_DIR)
# 	./$(DATA_GEN_TARGET)

# Regra para executar o processador de instâncias
# process: $(PROCESS_TARGET)
# 	@mkdir -p resultado
# 	./$(PROCESS_TARGET)

# Regra para executar o teste do algoritmo evolutivo
# test: $(TEST_TARGET)
# 	./$(TEST_TARGET) data/64/instance_0.txt test_output_file.txt

# Regras para compilar os arquivos fonte em arquivos objeto
# $(BIN_DIR)/DAG.o: $(SRC_DIR)/DAG.cpp $(INCLUDE_DIR)/DAG.hpp $(INCLUDE_DIR)/util.hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BIN_DIR)/instance.o: $(SRC_DIR)/instance.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/util.hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BIN_DIR)/simulated_annealing.o: $(SRC_DIR)/simulated_annealing.cpp $(INCLUDE_DIR)/simulated_annealing.hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BIN_DIR)/evolutionary_algorithm.o: $(SRC_DIR)/evolutionary_algorithm.cpp $(INCLUDE_DIR)/evolutionary_algorithm.hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BIN_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/instance.hpp $(INCLUDE_DIR)/DAG.hpp $(INCLUDE_DIR)/simulated_annealing.hpp $(INCLUDE_DIR)/evolutionary_algorithm.hpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos gerados
# clean:
# 	rm -f $(OBJS) $(TARGET) $(DATA_GEN_TARGET) $(PROCESS_TARGET) $(TEST_TARGET)

# Regra para executar o programa
# run: $(TARGET)
# 	./$(TARGET)

# Regra para forçar a recompilação
# .PHONY: all clean run data process test

.PHONY: data process
data:
	g++ src/data_generator.cpp -I include -o data_generator && ./data_generator


process:
	g++ src/process_instances.cpp src/DAG.cpp src/instance.cpp src/simulated_annealing.cpp src/evolutionary_algorithm.cpp -I include -O3 -DNDEBUG -o process_instances && ./process_instances