# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++20 -lstdc++

# Directories
SRC_DIR := src
BUILD_DIR := bin

all: bubble-sort bucket-sort insertion-sort quick-sort selection-sort

bubble-sort: build
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/bubble-sort.cc -o $(BUILD_DIR)/bubble-sort
	./$(BUILD_DIR)/bubble-sort

bucket-sort: build
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/bucket-sort.cc -o $(BUILD_DIR)/bucket-sort
	./$(BUILD_DIR)/bucket-sort

insertion-sort: build
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/insertion-sort.cc -o $(BUILD_DIR)/insertion-sort
	./$(BUILD_DIR)/insertion-sort

quick-sort: build
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/quick-sort.cc -o $(BUILD_DIR)/quick-sort
	./$(BUILD_DIR)/quick-sort

selection-sort: build
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/selection-sort.cc -o $(BUILD_DIR)/selection-sort
	./$(BUILD_DIR)/selection-sort

build:
	@mkdir -p $(BUILD_DIR)
 
clean:
	rm -rf $(BUILD_DIR)