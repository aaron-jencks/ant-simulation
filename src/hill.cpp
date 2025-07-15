#include <ants/hill.hpp>
#include <ants/utils.hpp>

#include <cstdlib>
#include <limits>
#include <GL/gl.h>

using namespace AntSim;

AntHill::AntHill(double x, double y, AntGenerator generator, double interval, double variability) : Entity(x, y), interval(interval), variability(variability), generator(generator) {
    reset_timer();
}

void AntHill::reset_timer() {
    current_counter = interval + random_variation(variability);
}

void AntHill::update(double dt, const UpdateContext& ctx) {
    if (!active || current_counter <= 0.0) return;
    current_counter -= dt;
    if (current_counter <= 0.0) {
        // spawn an ant
        ctx.grid->addEntity(generator(x, y));
        reset_timer();
    }
}

void AntHill::draw() const {
    double r = 2.0;

    // 168, 140, 62 light brown
    glColor3d(0.6588, 0.5490, 0.2431); // yellow
    glBegin(GL_QUADS);
    glVertex2d(x - r, y - r);
    glVertex2d(x + r, y - r);
    glVertex2d(x + r, y + r);
    glVertex2d(x - r, y + r);
    glEnd();
}
