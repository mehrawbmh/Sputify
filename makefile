PROJECT_EXE := sputify.out

CC := g++ --std=c++20
CC_FLAGS := --std=c++20
CCX := $(CC) $(CC_FLAGS)

HEADERS_DIR := headers
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := .

TARGET := $(BIN_DIR)/$(PROJECT_EXE)

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR);

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR);

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CCX) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o;

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o
	$(CCX) $(BUILD_DIR)/main.o -o $(TARGET);
	$(TARGET); #TODO: remove

.PHONY:
	clean

clean:
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);
