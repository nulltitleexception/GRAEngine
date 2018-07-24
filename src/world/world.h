#ifndef GRAE_ENGINE_WORLD_H
#define GRAE_ENGINE_WORLD_H

#include "cell.h"
#include "cellschematic.h"

namespace GRAE {
class Game;

class World {
public:
    Game *game;
    std::vector<Cell *> cells;
public:
    World(Game *g = nullptr);

    World(std::vector<Cell *> &c, Game *g);

    ~World();

    void update(double dt);

    void render();
};
}

#endif //GRAE_ENGINE_WORLD_H
