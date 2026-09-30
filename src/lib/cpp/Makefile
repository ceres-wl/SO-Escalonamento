CXX := em++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Isrc -MMD -MP 
#em++ -lembind -o src/lib/cpp/main.js src/lib/cpp/main.cpp -O3 -sEXPORT_ES6 --emit-tsd main.ts

SRC_DIR := .
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

TARGET := main.js

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(INCLUDES) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(BUILD_DIR)/$(TARGET)