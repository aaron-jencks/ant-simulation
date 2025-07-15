CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Iinclude

ANT_INCLUDE_PREFIX=include/ants
SRC_WITH_HEADERS = src/grid.cpp src/ant.cpp src/pheromone.cpp src/hill.cpp src/food.cpp
SRC = src/main.cpp src/glad.c $(SRC_WITH_HEADERS)
HEADERS_FROM_SRC_NAMES = $(patsubst src/%.cpp,%.hpp,$(SRC_WITH_HEADERS))
HEADERS_NAMES = utils.hpp entity.hpp context.hpp $(HEADER_FROM_SRC_NAMES)
HEAD = $(addprefix $(ANT_INCLUDE_PREFIX)/,$(HEADER_NAMES))
OUT = ant_sim

LIBS = -lglfw -lGL -lGLU -lm

$(OUT): $(SRC) $(HEAD)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

