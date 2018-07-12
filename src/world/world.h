#ifndef GRAE_ENGINE_WORLD_H
#define GRAE_ENGINE_WORLD_H

#include "cell.h"

namespace GRAE {
class World {
public:
    std::vector<Cell*> cells;
public:
    World();
    World(std::vector<Cell*> &c);
    World(std::string path, Resources *res, bool& success, std::string& reason);
    ~World();
    void update(double dt);
    void render();
};
}

#endif //GRAE_ENGINE_WORLD_H
