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
INCLUDE_DIRS = $(foreach includedir,$(CONAN_INCLUDE_DIRS),-I$(includedir))
CXXFLAGS += $(INCLUDE_DIRS)

# Source, object, and binary directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/movie_booking_service

# List of source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Create output directories if they do not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target to build the entire project
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Compile individual source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Clean up all generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
