#include "cell.h"

namespace GRAE {
Cell::Cell(World *w) : world(w) {}


Cell::Cell(CellSchematic *schematic, World *w) : world(w) {
    for (EntitySchematic *ent : schematic->ent) {
        entities.push_back(ent->newInstance(this));
    }
}

Cell::~Cell() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
}

void Cell::update(double dt) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(dt);
    }
}

void Cell::render() {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render();
    }
}
}