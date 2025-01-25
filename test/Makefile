CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET_DIR = ../bin
DATA_DIR = ../data
TARGET = $(TARGET_DIR)/pa.out
SRC = AVL.cpp
DATA_GEN_SRC = ../src/data_generator.cpp
DATA_GEN_TARGET = $(TARGET_DIR)/data_generator.out

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(DATA_GEN_TARGET): $(DATA_GEN_SRC)
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(DATA_GEN_TARGET) $(DATA_GEN_SRC)

clean:
	rm -f $(TARGET) $(DATA_GEN_TARGET)

run: $(TARGET)
	./$(TARGET)

data: $(DATA_GEN_TARGET)
	@mkdir -p $(DATA_DIR)
	./$(DATA_GEN_TARGET)

.PHONY: all clean run data
