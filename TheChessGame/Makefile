# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Define directories
OBJDIR = build
SRCDIR = src

# Define the source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Define the object files
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Define the target executable
TARGET = main

# OS-specific mkdir command
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(OBJDIR)" mkdir $(OBJDIR)
else
    MKDIR = mkdir -p $(OBJDIR)
endif

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR)  # Ensure the object directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean
