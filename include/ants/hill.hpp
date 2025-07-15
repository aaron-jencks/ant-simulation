#ifndef HILL_H
#define HILL_H

#include <ants/entity.hpp>
#include <ants/grid.hpp>
#include <ants/ant.hpp>

namespace AntSim {
    typedef Ant* (*AntGenerator)(double x, double y);

    class AntHill : public Entity {
        public:
            double interval;
            double current_counter = 0;
            double variability;
            bool active = true;
            AntGenerator generator;
            AntHill(double x, double y, AntGenerator generator, double interval, double variability = 0.0);
            void reset_timer();
            void update(double dt, const UpdateContext& ctx) override;
            void draw() const override;
    };
}

#endif
