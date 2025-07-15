#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <ants/grid.hpp>
#include <ants/hill.hpp>
#include <ants/food.hpp>
#include <ants/ant.hpp>
#include <ants/utils.hpp>

using namespace AntSim;

const int SIM_SPEED = 10;
const int SIM_WIDTH = 1000;
const int SIM_HEIGHT = 1000;

const double SIM_SPAWN_RATE = 5.0;
const double SIM_SPAWN_VARIATION = 2.0;

const double FOOD_BASE = 10.0;
const double FOOD_VARIATION = 5.0;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const double GRID_SPACING = 1.0;

void setupOrthoProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SIM_WIDTH, 0, SIM_HEIGHT); // match simulation space
    glMatrixMode(GL_MODELVIEW);
}

Ant* ant_generator(double x, double y) {
    return new Ant(x, y, (double)SIM_SPEED);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ant Sim", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    setupOrthoProjection();

    Grid grid(SIM_WIDTH, SIM_HEIGHT, GRID_SPACING);

    // Add ant hills
    for (int i = 0; i < 10; ++i) {
        double x = rand() % SIM_WIDTH;
        double y = rand() % SIM_HEIGHT;
        grid.addEntity(new AntHill(x, y, ant_generator, SIM_SPAWN_RATE, SIM_SPAWN_VARIATION));
    }

    // Add some food
    for (int i = 0; i < 50; ++i) {
        double x = rand() % SIM_WIDTH;
        double y = rand() % SIM_HEIGHT;
        double amount = FOOD_BASE + random_variation(FOOD_VARIATION);
        grid.addEntity(new Food(x, y, amount));
    }

    double prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double dt = currentTime - prevTime;
        prevTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        grid.updateAll(dt);
        grid.drawAll();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

