# define the C++ compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude

# define any libraries to link into executable
LIBS = -lGLEW -lglfw -lGL

# define the C++ source files
SRCS = $(wildcard source/*.cpp vendor/*.cpp)
TEST_SRCS = $(wildcard test/*.cpp)

OBJS = $(addprefix build/, $(notdir $(SRCS:.cpp=.o)))
TEST_OBJS = $(addprefix build/, $(notdir $(TEST_SRCS:.cpp=.o)))

# define the executable file 
MAIN = app
TEST_MAIN = test_app

all: $(MAIN)
	@echo  The app has been compiled

test: $(TEST_MAIN)
	@echo  The test app has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

$(TEST_MAIN): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_MAIN) $(OBJS) $(TEST_OBJS) $(LIBS)

build/%.o: source/%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@

build/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@

build/%.o: vendor/%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) build/*.o *~ $(MAIN) $(TEST_MAIN)

