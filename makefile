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

$(BUILD_DIR)/base_user.o: $(SRC_DIR)/base_user.cpp $(HEADERS_DIR)/base_user.hpp
	$(CCX) -c $(SRC_DIR)/base_user.cpp -o $(BUILD_DIR)/base_user.o

$(BUILD_DIR)/user.o: $(SRC_DIR)/user.cpp $(HEADERS_DIR)/user.hpp
	$(CCX) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/artist.o: $(SRC_DIR)/artist.cpp $(HEADERS_DIR)/artist.hpp
	$(CCX) -c $(SRC_DIR)/artist.cpp -o $(BUILD_DIR)/artist.o

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/base_user.o $(BUILD_DIR)/user.o $(BUILD_DIR)/artist.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/base_user.o -o $(TARGET);
	$(TARGET); #TODO: remove

.PHONY:
	clean

clean:
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);
