# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -I $(SRC_DIR)

# Directories
SRC_DIR = source
BUILD_DIR = release

# Output file
TARGET = $(BUILD_DIR)/program

# Libraries
LIBS = -lole32 -lodbc32

# Source files (add subdirectories as needed)
SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/app/*.cpp $(SRC_DIR)/controllers/*.cpp \
       $(SRC_DIR)/services/*.cpp $(SRC_DIR)/models/*.cpp $(SRC_DIR)/database/*.cpp \
       $(SRC_DIR)/factories/*.cpp $(SRC_DIR)/strategies/*.cpp $(SRC_DIR)/commands/*.cpp \
       $(SRC_DIR)/ui/*.cpp)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target - direct compilation similar to your command line
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean