.PHONY: all clean release \
        test test-unit test-ci

CXX ?= g++

WARNINGS = \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wno-unused-parameter

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
TEST_TARGET = unit_tests

BUILD_DIR = build

# =========================
# Sources
# =========================

SRC := $(wildcard src/*.cpp) \
       $(wildcard src/*/*.cpp)

SRC_NO_MAIN := $(filter-out src/main.cpp,$(SRC))

TEST_SRC := tests/unit/unit_tests.cpp

# =========================
# Objects
# =========================

OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

TEST_OBJ := \
	$(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC_NO_MAIN)) \
	$(BUILD_DIR)/unit_tests.o

DEP := $(OBJ:.o=.d)

# =========================
# Main Targets
# =========================

all: release

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# =========================
# Test Targets
# =========================

test: test-unit test-ci

test-unit: CXXFLAGS += $(TEST_FLAGS) $(STRICT_WARNINGS)
test-unit: LDFLAGS += $(TEST_FLAGS)
test-unit: $(TEST_TARGET)
	./$(TEST_TARGET)

test-ci: CXXFLAGS += $(TEST_FLAGS) $(STRICT_WARNINGS)
test-ci: LDFLAGS += $(TEST_FLAGS)
test-ci: $(TARGET)
	bash tests/run_tests.sh

# =========================
# Main binary
# =========================

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

# =========================
# Unit tests binary
# =========================

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) $(LDFLAGS) -o $(TEST_TARGET)

# =========================
# Compilation Rules
# =========================

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/unit_tests.o: tests/unit/unit_tests.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# =========================
# Cleanup
# =========================

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

-include $(DEP)
