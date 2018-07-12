#include "world.h"

namespace GRAE {
World::World() {

}

World::World(std::vector<Cell *> &c) {
    cells.insert(cells.end(), c.begin(), c.end());
}

World::World(std::string path, Resources *res, bool &success, std::string &reason) {

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