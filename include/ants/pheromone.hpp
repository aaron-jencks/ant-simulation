#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <ants/entity.hpp>
#include <ants/grid.hpp>

namespace AntSim {
	class Pheromone : public Entity {
		public:
			double intensity, decayRate;
			Pheromone(double x, double y, double intensity, double decayRate);
			bool isDead() const override;
			void update(double dt, const UpdateContext& ctx) override;
			void draw() const override;
	};
}

#endif
