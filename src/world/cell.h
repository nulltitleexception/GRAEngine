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

    virtual ~Cell();

    virtual void update(double dt);

    virtual void render();
};

class TerrainCell : public Cell {
private:
    std::unique_ptr<float> terrain;
    int width, height;
public:
    explicit TerrainCell(World *w);

    TerrainCell(CellSchematic *schematic, World *w);

    virtual ~TerrainCell();

    virtual void update(double dt);

    virtual void render();
};
}

#endif //GRAE_ENGINE_CELL_H
