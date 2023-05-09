CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude
LDFLAGS =
LIBS = -lGLEW -lglfw -lGL
SRCDIR = source
INCDIR = include
BUILDDIR = build
TESTDIR = test
TARGET = app
TARGET_TEST = test_app
SRC_EXT = cpp

# Recursively find all source files and corresponding object files
SRCS = $(shell find $(SRCDIR) -type f -name *.$(SRC_EXT))
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRC_EXT)=.o))

# Recursively find all test source files and corresponding object files
TEST_SRCS = $(shell find $(TESTDIR) -type f -name *.$(SRC_EXT))
TEST_OBJS = $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SRCS:.$(SRC_EXT)=.o))

# Default target
all: $(TARGET)

# Compile the main target
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile the test target
$(TARGET_TEST): CXXFLAGS += -DENABLE_TEST
$(TARGET_TEST): $(OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC_EXT)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile test object files
$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRC_EXT)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Test target
test: $(TARGET_TEST)

# Clean up
clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TARGET_TEST)

.PHONY: all test clean

