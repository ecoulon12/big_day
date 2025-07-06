# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
TARGET = big_day

# Source files
SRCS = main.cpp

# Object files (auto-generated)
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
