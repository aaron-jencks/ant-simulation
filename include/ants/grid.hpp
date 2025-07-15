#ifndef GRID_H
#define GRID_H

#include <vector>
#include <ants/entity.hpp>

namespace AntSim {
	class Grid {
		public:
			size_t height;
			size_t width;
            double spacing;
			std::vector<std::vector<std::vector<Entity*>>> cells;
            std::vector<std::vector<std::vector<Entity*>>> next_cells;
			bool in_update = false;

			Grid(size_t h, size_t w, double s);
			void addEntity(Entity* e);
			void updateAll(double dt);
			void drawAll() const;
	};
}

#endif
