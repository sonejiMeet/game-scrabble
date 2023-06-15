CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -O2 -I./src
# LDFLAGS =

SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_DIR = ./test_t

headers := $(wildcard $(SRC_DIR)/*.h)

sources := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC = $(TEST_DIR)/test.cpp

objects := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(sources))
TEST_OBJ = $(TEST_SRC:.cpp=.o)

executable = scrabble
test_executable = test_scrabble

$(executable): $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(test_executable): $(TEST_OBJ) $(filter-out $(OBJ_DIR)/main.o, $(objects))
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(headers)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(headers)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(executable)
	./$(executable)

build-test: $(test_executable)

run-test: $(test_executable)
	./$(test_executable)

clean:
	find $(OBJ_DIR) $(TEST_DIR) -name '*.o' -exec rm -rf {} +
	rm -rf $(executable) $(test_executable)

# make : builds project
# make run : runs scrabble program
# make build-test : builds test project
# make run-test : runs test program