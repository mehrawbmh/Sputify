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

$(BUILD_DIR)/view.o: $(SRC_DIR)/view.cpp $(HEADERS_DIR)/view.hpp
	$(CCX) -c $(SRC_DIR)/view.cpp -o $(BUILD_DIR)/view.o

$(BUILD_DIR)/db.o: $(SRC_DIR)/db.cpp $(HEADERS_DIR)/db.hpp
	$(CCX) -c $(SRC_DIR)/db.cpp -o $(BUILD_DIR)/db.o

$(BUILD_DIR)/client_exception.o: $(SRC_DIR)/client_exception.cpp $(HEADERS_DIR)/client_exception.hpp
	$(CCX) -c $(SRC_DIR)/client_exception.cpp -o $(BUILD_DIR)/client_exception.o

$(BUILD_DIR)/base_user.o: $(SRC_DIR)/base_user.cpp $(HEADERS_DIR)/base_user.hpp
	$(CCX) -c $(SRC_DIR)/base_user.cpp -o $(BUILD_DIR)/base_user.o

$(BUILD_DIR)/user.o: $(SRC_DIR)/user.cpp $(HEADERS_DIR)/user.hpp
	$(CCX) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/artist.o: $(SRC_DIR)/artist.cpp $(HEADERS_DIR)/artist.hpp
	$(CCX) -c $(SRC_DIR)/artist.cpp -o $(BUILD_DIR)/artist.o

$(BUILD_DIR)/users_controller.o: $(SRC_DIR)/users_controller.cpp $(HEADERS_DIR)/users_controller.hpp
	$(CCX) -c $(SRC_DIR)/users_controller.cpp -o $(BUILD_DIR)/users_controller.o

$(BUILD_DIR)/users_model.o: $(SRC_DIR)/users_model.cpp $(HEADERS_DIR)/users_model.hpp
	$(CCX) -c $(SRC_DIR)/users_model.cpp -o $(BUILD_DIR)/users_model.o

$(BUILD_DIR)/command_manager.o: $(SRC_DIR)/command_manager.cpp $(HEADERS_DIR)/command_manager.hpp
	$(CCX) -c $(SRC_DIR)/command_manager.cpp -o $(BUILD_DIR)/command_manager.o

$(BUILD_DIR)/tag.o: $(SRC_DIR)/tag.cpp $(HEADERS_DIR)/tag.hpp
	$(CCX) -c $(SRC_DIR)/tag.cpp -o $(BUILD_DIR)/tag.o

$(BUILD_DIR)/music.o: $(SRC_DIR)/music.cpp $(HEADERS_DIR)/music.hpp
	$(CCX) -c $(SRC_DIR)/music.cpp -o $(BUILD_DIR)/music.o

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/view.o $(BUILD_DIR)/base_user.o $(BUILD_DIR)/user.o $(BUILD_DIR)/artist.o $(BUILD_DIR)/command_manager.o $(BUILD_DIR)/users_model.o $(BUILD_DIR)/users_controller.o $(BUILD_DIR)/client_exception.o $(BUILD_DIR)/db.o $(BUILD_DIR)/tag.o $(BUILD_DIR)/music.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/view.o $(BUILD_DIR)/base_user.o $(BUILD_DIR)/user.o $(BUILD_DIR)/artist.o $(BUILD_DIR)/command_manager.o $(BUILD_DIR)/users_model.o $(BUILD_DIR)/users_controller.o $(BUILD_DIR)/client_exception.o $(BUILD_DIR)/db.o $(BUILD_DIR)/tag.o $(BUILD_DIR)/music.o -o $(TARGET)


.PHONY:
	clean

clean:
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);
