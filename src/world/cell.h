#ifndef GRAE_ENGINE_CELL_H
#define GRAE_ENGINE_CELL_H

#include "entity/entity.h"

#include <vector>

namespace GRAE {
class CellSchematic;

class World;


class Cell {
public:
    World *world;
    std::vector<Entity *> entities;
public:
    explicit Cell(World *w);

    Cell(CellSchematic *schematic, World *w);

    ~Cell();

    void update(double dt);

    void render();
};
}

#endif //GRAE_ENGINE_CELL_H
