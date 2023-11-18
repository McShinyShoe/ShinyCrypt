CMAKE = cmake
MAKE = make
CXX = g++
CXXSTD=c++11
CXXINCLUDE = include/
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=$(CXXSTD) -g -fsanitize=address
LDFLAGS =  -fsanitize=address
LBLIBS = 
BUILD_DIR = build
TEST_DIR = test
BIN_DIR = bin
TEST_SRC = example/test.cpp
LIB = base.a sha.a

.PHONY: all build clean test

all: build
	$(MAKE) -C $(BUILD_DIR) all
	mv $(BUILD_DIR)/*.a $(BIN_DIR)/

build:
	mkdir -p $(BUILD_DIR)
	$(CMAKE) . -B $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

test: all
	cp $(BIN_DIR)/* $(TEST_DIR)
	$(CXX) $(LDFLAGS) -o $(TEST_DIR)/$@ $(TEST_SRC) $(addprefix $(TEST_DIR)/lib,$(LIB)) $(LBLIBS) $(addprefix -I,$(CXXINCLUDE))
	$(TEST_DIR)/$@ $(str)

$(LIB): build
	$(MAKE) -C $(BUILD_DIR) $(@:.a=)
	mv $(BUILD_DIR)/lib$@ $(BIN_DIR)/

