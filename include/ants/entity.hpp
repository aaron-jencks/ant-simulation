#ifndef ENTITY_H
#define ENTITY_H

#include <ants/context.hpp>

namespace AntSim {
	class Entity {
		public:
			double x, y;

			Entity(double x, double y): x(x), y(y) {}
			virtual ~Entity() {}

			virtual bool isDead() const { return false; }
			virtual void update(double dt, const UpdateContext& ctx) = 0;
			virtual void draw() const = 0;
	};
}

#endif
