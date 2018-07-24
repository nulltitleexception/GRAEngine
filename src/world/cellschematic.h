#ifndef GRAE_ENGINE_CELLSCHEMATIC_H
#define GRAE_ENGINE_CELLSCHEMATIC_H

#include "entity/entityschematic.h"

#include <vector>
#include <string>

namespace GRAE {
class Cell;

class World;

class CellSchematic {
    friend class Cell;

private:
    std::vector<EntitySchematic *> ent;
public:

    explicit CellSchematic(Resources *res);

    CellSchematic(std::string s, Resources *res, bool &success, std::string &reason);

    Cell *newInstance(World *w);

    void addEntity(EntitySchematic *schematic);
};
}

#endif //GRAE_ENGINE_CELLSCHEMATIC_H
