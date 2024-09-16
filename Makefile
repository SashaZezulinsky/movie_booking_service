# Set the directory for Conan's installation files
CONAN_INSTALL_DIR = conan_install

# Include Conan's generated make dependencies
ifeq (,$(wildcard $(CONAN_INSTALL_DIR)/conandeps.mk))
    $(shell conan install . --build=missing -of=$(CONAN_INSTALL_DIR))
endif
include $(CONAN_INSTALL_DIR)/conandeps.mk

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -DASIO_STANDALONE

# Include paths from Conan dependencies
INCLUDE_DIRS = $(foreach includedir,$(CONAN_INCLUDE_DIRS),-I$(includedir)) -I./src
CXXFLAGS += $(INCLUDE_DIRS)

# Linker settings (include paths for libraries)
LIB_DIRS = $(foreach libdir,$(CONAN_LIB_DIRS),-L$(libdir))
LDFLAGS += $(LIB_DIRS)

# Linker settings for Windows (for Winsock and Google Test)
ifeq ($(OS),Windows_NT)
    LDFLAGS += -lws2_32 -lmswsock -lgtest -lgtest_main
    INCLUDE_DIRS += -IC:/Users/runneradmin/.conan2/p/b/gtest50c700540ab27/p/include
    LIB_DIRS += -LC:/Users/runneradmin/.conan2/p/b/gtest50c700540ab27/p/lib
else
    GTEST_LIBS = -lgtest -lgtest_main -lpthread
endif

# Source, object, and binary directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DOCS_DIR = docs
TEST_DIR = tests
TEST_OBJ_DIR = obj/tests

TARGET = $(BIN_DIR)/movie_booking_service
TEST_TARGET = $(BIN_DIR)/test_booking_system

# List of source and object files for main program
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test source files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)

# Create output directories if they do not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target to build the entire project
build: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Compile individual source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Separate target to build the tests (without linking main.cpp)
$(TEST_TARGET): $(BIN_DIR) $(TEST_OBJ_DIR) $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) $(LDFLAGS) $(GTEST_LIBS) -o $(TEST_TARGET)

# Compile individual test source files into object files
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the unit tests
test: $(TEST_OBJ_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up all generated files
clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(BIN_DIR) $(CONAN_INSTALL_DIR) $(DOCS_DIR)

# Generate documentation with Doxygen
docs:
	doxygen $(DOXYGEN_CONFIG)

# Build Docker image
docker:
	docker build -t movie_booking_service .

# Run the service
run: build
	./$(TARGET)

.PHONY: build clean docs docker run test
