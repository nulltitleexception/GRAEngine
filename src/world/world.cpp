#include "world.h"

namespace GRAE {
World::World(Game *g) : game(g) {}

World::World(std::vector<Cell *> &c, Game *g) : game(g) {
    cells.insert(cells.end(), c.begin(), c.end());
}

World::~World() {
    for (int i = 0; i < cells.size(); i++) {
        delete cells[i];
    }
}

void World::update(double dt) {
    for (int i = 0; i < cells.size(); i++) {
        cells[i]->update(dt);
    }
}

void World::render() {
    for (int i = 0; i < cells.size(); i++) {
        cells[i]->render();
    }
}
}