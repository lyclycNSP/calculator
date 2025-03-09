CXXFLAGS = -Wall -Werror -pedantic -Wconversion -Wsign-conversion -std=c++23
CPPFLAGS = -Ilib

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIB_DIR)/calculator.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

.PHONY:clean
clean:
	rm -rf $(BUILD_DIR)/* $(LIB_DIR)/*~ *~
