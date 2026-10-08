CC = gcc
CXX = g++

CPPFLAGS = -Iinclude
CXXFLAGS = -g -std=c++20 -Wall -MMD -MP
CFLAGS = -g -Wall -MMD -MP
LDLIBS = -lglfw -lGL -lGLU -lm

OUT = ant_sim
TEST_OUT = build/tests/test_runner

CPP_SOURCES := $(shell find src -type f -name '*.cpp')
C_SOURCES := $(shell find src -type f -name '*.c')
TEST_SOURCES := $(shell find tests -type f -name '*.cpp')

OBJECTS := $(patsubst src/%,build/%.o,$(CPP_SOURCES) $(C_SOURCES))
TEST_OBJECTS := $(patsubst tests/%,build/tests/%.o,$(TEST_SOURCES))
TEST_SUPPORT_OBJECTS := $(filter-out build/main.cpp.o,$(OBJECTS))

DEPS := $(OBJECTS:.o=.d)
TEST_DEPS := $(TEST_OBJECTS:.o=.d)

.PHONY: all build-tests clean test

all: $(OUT)

build-tests: $(TEST_OUT)

test: $(TEST_OUT)
	./$(TEST_OUT)

$(OUT): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(TEST_OUT): $(TEST_OBJECTS) $(TEST_SUPPORT_OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

build/%.cpp.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/%.c.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/tests/%.cpp.o: tests/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(OUT)

-include $(DEPS)
-include $(TEST_DEPS)
