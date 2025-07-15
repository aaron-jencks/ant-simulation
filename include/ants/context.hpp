#ifndef CONTEXT_H
#define CONTEXT_H

namespace AntSim {
    class Grid; // defined in grid.hpp, avoid circular import

    class UpdateContext {
        public:
        Grid* grid;

        UpdateContext(Grid* grid) : grid(grid) {}
    };
}

#endif
