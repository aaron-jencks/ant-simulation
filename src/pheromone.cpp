#include <GL/gl.h> // immediate mode for quick drawing

#include <ants/pheromone.hpp>

using namespace AntSim;

Pheromone::Pheromone(double x, double y, double intensity, double decayRate) : Entity(x, y), intensity(intensity), decayRate(decayRate) {}

void Pheromone::update(double dt, const UpdateContext& ctx) {
	intensity -= decayRate * dt;
	if(intensity < 0.0) intensity = 0.0;
}

void Pheromone::draw() const {
	if (intensity <= 0.0) return;

    	// Use alpha based on intensity for now (normalized to [0, 1])
    	double alpha = intensity;
    	if (alpha > 1.0) alpha = 1.0;

    	glColor4d(0.0, 1.0, 1.0, alpha); // cyan with variable transparency

    	double r = 1.5; // radius
    	glBegin(GL_QUADS);
    	glVertex2d(x - r, y - r);
    	glVertex2d(x + r, y - r);
    	glVertex2d(x + r, y + r);
    	glVertex2d(x - r, y + r);
    	glEnd();
}

bool Pheromone::isDead() const {
	return intensity <= 0.0;
}
