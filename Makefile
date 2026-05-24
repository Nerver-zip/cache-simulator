.PHONY: all clean test release

CXX ?= g++

WARNINGS = \
	-Wall \
	-Wextra \
	-Wpedantic

STRICT_WARNINGS = -Werror

STD = -std=c++20

RELEASE_FLAGS = -O3

TEST_FLAGS = \
	-O0 \
	-g \
	-fsanitize=address \
	-fsanitize=undefined

CXXFLAGS = $(STD) $(WARNINGS)

LDFLAGS =

TARGET = cache_simulator

BUILD_DIR = build

SRC := $(wildcard src/*.cpp) \
       $(wildcard src/*/*.cpp)

OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

DEP := $(OBJ:.o=.d)

all: release

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

test: CXXFLAGS += $(TEST_FLAGS) $(STRICT_WARNINGS)
test: LDFLAGS += $(TEST_FLAGS)
test: clean $(TARGET)
	bash scripts/run_tests.sh

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEP)
