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
    explicit Cell(Resources *res);

    Cell(std::string s, Resources *res, bool &success, std::string &reason);

    virtual ~Cell();

    virtual void update(double dt);

    virtual void render();
};

class TerrainCell : public Cell {
private:
    std::unique_ptr<float> terrain;
    int width, height;
    std::unique_ptr<Mesh> mesh;
public:
    explicit TerrainCell(Resources *res);

    TerrainCell(std::string s, Resources *res, bool &success, std::string &reason);

    virtual ~TerrainCell();

    virtual void update(double dt);

    virtual void render();
};
}

#endif //GRAE_ENGINE_CELL_H
