CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -pedantic -I include
LDLIBS = -lGLEW -lglfw -lGL

SRC_DIR = source
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build

# Find all source files in source directory
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
# Create a list of object files from the source files
OBJECTS := $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
# Create a list of dependencies for each object file
DEPS := $(OBJECTS:.o=.d)

# Compile all object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Link object files into executable
app: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

# Compile all test files
tests: $(wildcard $(TEST_DIR)/*.cpp) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

.PHONY: clean

# Remove all object files and executable
clean:
	$(RM) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d app tests

# Include dependency files
-include $(DEPS)

