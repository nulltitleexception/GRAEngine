#ifndef GRAE_ENGINE_CELL_H
#define GRAE_ENGINE_CELL_H

#include "entity/entity.h"
#include "resource/resources.h"

#include <vector>
#include <string>

namespace GRAE {
class CellSchematic;

class Cell {
public:
    std::vector<Entity *> entities;
public:
    Cell();

    explicit Cell(CellSchematic *schematic);

    ~Cell();

    void update(double dt);

    void render();
};
}

#endif //GRAE_ENGINE_CELL_H
