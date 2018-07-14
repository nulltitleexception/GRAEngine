#include "cell.h"
#include "cellschematic.h"

namespace GRAE {
Cell::Cell() {}


Cell::Cell(CellSchematic *schematic) {
    for (EntitySchematic *ent : schematic->ent) {
        entities.push_back(ent->newInstance());
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