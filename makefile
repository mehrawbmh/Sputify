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

$(BUILD_DIR)/format_exception.o: $(SRC_DIR)/format_exception.cpp $(HEADERS_DIR)/format_exception.hpp
	$(CCX) -c $(SRC_DIR)/format_exception.cpp -o $(BUILD_DIR)/format_exception.o

$(BUILD_DIR)/unique_exception.o: $(SRC_DIR)/unique_exception.cpp $(HEADERS_DIR)/unique_exception.hpp
	$(CCX) -c $(SRC_DIR)/unique_exception.cpp -o $(BUILD_DIR)/unique_exception.o

$(BUILD_DIR)/entity.o: $(SRC_DIR)/entity.cpp $(HEADERS_DIR)/entity.hpp
	$(CCX) -c $(SRC_DIR)/entity.cpp -o $(BUILD_DIR)/entity.o

$(BUILD_DIR)/base_user.o: $(SRC_DIR)/base_user.cpp $(HEADERS_DIR)/base_user.hpp $(HEADERS_DIR)/entity.hpp
	$(CCX) -c $(SRC_DIR)/base_user.cpp -o $(BUILD_DIR)/base_user.o

$(BUILD_DIR)/user.o: $(SRC_DIR)/user.cpp $(HEADERS_DIR)/user.hpp $(HEADERS_DIR)/base_user.hpp
	$(CCX) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/artist.o: $(SRC_DIR)/artist.cpp $(HEADERS_DIR)/artist.hpp $(HEADERS_DIR)/base_user.hpp
	$(CCX) -c $(SRC_DIR)/artist.cpp -o $(BUILD_DIR)/artist.o

$(BUILD_DIR)/users_controller.o: $(SRC_DIR)/users_controller.cpp $(HEADERS_DIR)/users_controller.hpp
	$(CCX) -c $(SRC_DIR)/users_controller.cpp -o $(BUILD_DIR)/users_controller.o

$(BUILD_DIR)/users_model.o: $(SRC_DIR)/users_model.cpp $(HEADERS_DIR)/users_model.hpp
	$(CCX) -c $(SRC_DIR)/users_model.cpp -o $(BUILD_DIR)/users_model.o

# $(BUILD_DIR)/command_manager.o: $(SRC_DIR)/command_manager.cpp $(HEADERS_DIR)/command_manager.hpp
#	$(CCX) -c $(SRC_DIR)/command_manager.cpp -o $(BUILD_DIR)/command_manager.o

$(BUILD_DIR)/tag.o: $(SRC_DIR)/tag.cpp $(HEADERS_DIR)/tag.hpp
	$(CCX) -c $(SRC_DIR)/tag.cpp -o $(BUILD_DIR)/tag.o

$(BUILD_DIR)/music.o: $(SRC_DIR)/music.cpp $(HEADERS_DIR)/music.hpp $(HEADERS_DIR)/entity.hpp
	$(CCX) -c $(SRC_DIR)/music.cpp -o $(BUILD_DIR)/music.o

$(BUILD_DIR)/musics_model.o: $(SRC_DIR)/musics_model.cpp $(HEADERS_DIR)/musics_model.hpp
	$(CCX) -c $(SRC_DIR)/musics_model.cpp -o $(BUILD_DIR)/musics_model.o

$(BUILD_DIR)/musics_controller.o: $(SRC_DIR)/musics_controller.cpp $(HEADERS_DIR)/musics_controller.hpp
	$(CCX) -c $(SRC_DIR)/musics_controller.cpp -o $(BUILD_DIR)/musics_controller.o

$(BUILD_DIR)/play_list.o: $(SRC_DIR)/play_list.cpp $(HEADERS_DIR)/play_list.hpp $(HEADERS_DIR)/entity.hpp
	$(CCX) -c $(SRC_DIR)/play_list.cpp -o $(BUILD_DIR)/play_list.o

$(BUILD_DIR)/handlers.o: $(SRC_DIR)/handlers.cpp $(HEADERS_DIR)/handlers.hpp
	$(CCX) -c $(SRC_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/sputify.o: $(SRC_DIR)/sputify.cpp $(HEADERS_DIR)/sputify.hpp
	$(CCX) -c $(SRC_DIR)/sputify.cpp -o $(BUILD_DIR)/sputify.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/base_user.o $(BUILD_DIR)/user.o $(BUILD_DIR)/artist.o $(BUILD_DIR)/users_model.o $(BUILD_DIR)/users_controller.o $(BUILD_DIR)/client_exception.o $(BUILD_DIR)/db.o $(BUILD_DIR)/tag.o $(BUILD_DIR)/music.o $(BUILD_DIR)/musics_controller.o $(BUILD_DIR)/musics_model.o $(BUILD_DIR)/play_list.o $(BUILD_DIR)/view.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/format_exception.o $(BUILD_DIR)/unique_exception.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/sputify.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/view.o $(BUILD_DIR)/base_user.o $(BUILD_DIR)/user.o $(BUILD_DIR)/artist.o $(BUILD_DIR)/users_model.o $(BUILD_DIR)/users_controller.o $(BUILD_DIR)/client_exception.o $(BUILD_DIR)/db.o $(BUILD_DIR)/tag.o $(BUILD_DIR)/music.o $(BUILD_DIR)/musics_controller.o $(BUILD_DIR)/musics_model.o $(BUILD_DIR)/play_list.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/format_exception.o $(BUILD_DIR)/unique_exception.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o  $(BUILD_DIR)/utilities.o $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/sputify.o -o $(TARGET)


.PHONY:
	clean

clean:
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);
