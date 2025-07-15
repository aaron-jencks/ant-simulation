#include <ants/food.hpp>

#include <GL/gl.h>

using namespace AntSim;

Food::Food(double x, double y, double amount) : Entity(x, y), amount(amount) {}
bool Food::isDead() const {
    return amount <= 0.0;
}
void Food::update(double dt, const UpdateContext& ctx) {}
void Food::draw() const {
    double r = 2.0;

    // 219, 86, 215 pink
    glColor3d(0.8588, 0.3733, 0.8431); // yellow ant
    glBegin(GL_QUADS);
    glVertex2d(x - r, y - r);
    glVertex2d(x + r, y - r);
    glVertex2d(x + r, y + r);
    glVertex2d(x - r, y + r);
    glEnd();
}