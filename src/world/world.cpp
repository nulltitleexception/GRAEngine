#include "world.h"

namespace GRAE {
World::World(Resources *res) : game(nullptr) {}

World::World(std::string s, Resources *res, bool &success, std::string &reason) : game(nullptr) {}

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

void World::addCell(Cell *c) {
    c->world = this;
    cells.push_back(c);
}
}


{
std::unordered_map<std::type_index, int> offsets;
void *p = new P();
std::type_index typeOfP;
Type *t = TypeImpl<P>;
Base *b;
std::type_index typeOfBase;
b = (Base*)p;


}