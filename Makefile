.PHONY: all clean release \
        test test-unit test-ci

CXX ?= g++

WARNINGS = \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wno-unused-parameter

STRICT_WARNINGS = -Werror

STD = -std=c++23

RELEASE_FLAGS = -O3

TEST_FLAGS = \
	-O0 \
	-g \
	-fsanitize=address \
	-fsanitize=undefined

COMMON_FLAGS = $(STD) $(WARNINGS)

LDFLAGS =

TARGET = cache_simulator
TEST_TARGET = unit_tests

# =========================
# Build directories
# =========================

BUILD_DIR = build

RELEASE_DIR = $(BUILD_DIR)/release
TEST_DIR = $(BUILD_DIR)/test

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

RELEASE_OBJ := \
	$(patsubst src/%.cpp,$(RELEASE_DIR)/%.o,$(SRC))

TEST_OBJ := \
	$(patsubst src/%.cpp,$(TEST_DIR)/%.o,$(SRC_NO_MAIN)) \
	$(TEST_DIR)/unit_tests.o

# =========================
# Dependencies
# =========================

DEP := \
	$(RELEASE_OBJ:.o=.d) \
	$(TEST_OBJ:.o=.d)

# =========================
# Main Targets
# =========================

all: release

release: $(TARGET)

# =========================
# Test Targets
# =========================

test: test-unit test-ci

test-unit: $(TEST_TARGET)
	./$(TEST_TARGET)

test-ci: $(TARGET)
	bash tests/run_tests.sh

# =========================
# Main binary
# =========================

$(TARGET): $(RELEASE_OBJ)
	@echo "[LINK] $@"
	@$(CXX) $(RELEASE_OBJ) $(LDFLAGS) -o $@

# =========================
# Unit tests binary
# =========================

$(TEST_TARGET): $(TEST_OBJ)
	@echo "[LINK] $@"
	@$(CXX) $(TEST_OBJ) $(LDFLAGS) $(TEST_FLAGS) -o $@

# =========================
# Release compilation
# =========================

$(RELEASE_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX][RELEASE] $<"
	@$(CXX) \
		$(COMMON_FLAGS) \
		$(RELEASE_FLAGS) \
		-MMD -MP \
		-c $< \
		-o $@

# =========================
# Test compilation
# =========================

$(TEST_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX][TEST] $<"
	@$(CXX) \
		$(COMMON_FLAGS) \
		$(STRICT_WARNINGS) \
		$(TEST_FLAGS) \
		-MMD -MP \
		-c $< \
		-o $@

$(TEST_DIR)/unit_tests.o: tests/unit/unit_tests.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX][TEST] $<"
	@$(CXX) \
		$(COMMON_FLAGS) \
		$(STRICT_WARNINGS) \
		$(TEST_FLAGS) \
		-MMD -MP \
		-c $< \
		-o $@

# =========================
# Cleanup
# =========================

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

# =========================
# Auto dependencies
# =========================

-include $(DEP)
