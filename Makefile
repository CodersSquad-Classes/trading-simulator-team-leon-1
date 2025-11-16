CXX = g++
SRC_DIR = src
BUILD_DIR = build
TARGET_NAME = main
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TARGET = $(TARGET_NAME)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)