#include <ants/grid.hpp>
#include <ants/context.hpp>

using namespace AntSim;

Grid::Grid(size_t h, size_t w, double s) : height(h), width(w), spacing(s) {
	cells.resize(height, std::vector<std::vector<Entity*>>(width));
    next_cells = cells; // deep copy
}

void Grid::addEntity(Entity* e) {
	size_t cx = static_cast<size_t>(e->x / spacing);
	size_t cy = static_cast<size_t>(e->y / spacing);
	if(cx > 0 && cx < width && cy > 0 && cy < height) {
		if (in_update)
			next_cells[cy][cx].push_back(e);
		else
			cells[cy][cx].push_back(e);
	}
}

void Grid::updateAll(double dt) {
	in_update = true;

    UpdateContext ctx(this);

	for (auto& row : cells) {
       	for (auto& cell : row) {
       		for (auto it = cell.begin(); it != cell.end(); ) {
       			Entity* e = *it;

       			e->update(dt, ctx);

                size_t cx = static_cast<size_t>(e->x / spacing);
                size_t cy = static_cast<size_t>(e->y / spacing);

       			if (e->isDead()) {
					delete e;
                } else if (cx >= 0 && cx < width && cy >= 0 && cy < height) {
					next_cells[cy][cx].push_back(e);
            	}

				++it;
        	}
    	}
	}

    // clear the current grid for swapping
    for (auto& row : cells) {
        for(auto& cell : row) 
            cell.clear();
    }

    std::swap(cells, next_cells);

	in_update = false;
}

void Grid::drawAll() const {
	for(const auto& row : cells) {
		for(const auto& cell : row) {
			for(const Entity* e : cell) {
				e->draw();
			}
		}
	}
}
