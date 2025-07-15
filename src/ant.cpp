#include <cmath>
#include <cstdlib> // for rand
#include <GL/gl.h> // for simple immediate mode drawing (optional for now)

#include <ants/ant.hpp>

using namespace AntSim;

Ant::Ant(double x, double y, double speed) : Entity(x, y), speed(speed) {}

void Ant::update(double dt, const UpdateContext& ctx) {
    	// Slight random wiggle
    	double deltaAngle = ((rand() % 100) / 100.0 - 0.5) * 0.2;
    	angle += deltaAngle;

    	// Move forward
    	x += std::cos(angle) * speed * dt;
    	y += std::sin(angle) * speed * dt;

        double gw = ctx.grid->width * ctx.grid->spacing;
        double gh = ctx.grid->height * ctx.grid->spacing;

        if (x < 0) {
            x = gw + x;
        } else if (x >= gw) {
            x -= gw;
        }

        if (y < 0) {
            y = gh + y;
        } else if (y >= gh) {
            y -= gh;
        }
}

void Ant::draw() const {
	// Immediate mode for prototyping only (will replace with shader later)
	double r = 2.0;

	glColor3d(1.0, 1.0, 0.0); // yellow ant
	glBegin(GL_QUADS);
	glVertex2d(x - r, y - r);
	glVertex2d(x + r, y - r);
	glVertex2d(x + r, y + r);
	glVertex2d(x - r, y + r);
	glEnd();
}
