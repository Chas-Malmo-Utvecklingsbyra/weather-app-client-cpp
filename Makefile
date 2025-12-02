# Compiler
CXX := g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g

# Name of the final binary
BIN := main

#
BIN_DELETE := main.o

# Source directory
SRC_DIR := src

# Directory where object files will be placed
BUILD_DIR := build

CPPFLAGS :=-g -pthread 

# Find all .cpp source files in SRC_DIR and its subdirectories
SRCS := $(shell find -L $(SRC_DIR) -type f -name '*.cpp')

# Object files 
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(BIN) run

# Rule to link object files into the target executable
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJS)
# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(BIN)
	./$(BIN)

# Clean rule to remove generated files
clean:
	rm -f $(BIN) $(BIN_DELETE) $(OBJS)
