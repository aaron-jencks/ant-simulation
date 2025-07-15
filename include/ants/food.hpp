#ifndef FOOD_H
#define FOOD_H

#include <ants/entity.hpp>

namespace AntSim {
    class Food : public Entity {
        public:
            double amount;

            Food(double x, double y, double amount);
            bool isDead() const override;
            void update(double dt, const UpdateContext& ctx) override;
			void draw() const override;
    };
}

#endif