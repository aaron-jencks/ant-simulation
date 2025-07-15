#ifndef ANT_H
#define ANT_H

#include <ants/entity.hpp>
#include <ants/grid.hpp>

namespace AntSim {
	enum AntStates {
		Searching,
		Returning
	};

	class Ant : public Entity {
		public:
			double angle = 0.0, speed;
			double capacity = 10.0;
			double vision_distance, vision_angle;
			AntStates state = AntStates::Searching;
			Ant(double x, double y, double speed);
			void update(double dt, const UpdateContext& ctx) override;
			void draw() const override;
	};
}

#endif
