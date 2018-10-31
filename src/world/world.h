#ifndef GRAE_ENGINE_WORLD_H
#define GRAE_ENGINE_WORLD_H

#include "cell.h"

namespace GRAE {
class Game;

class World {
public:
    Game *game;
private:
    std::vector<Cell *> cells;
public:
    explicit World(Resources *res);

    World(std::string s, Resources *res, bool &success, std::string &reason);

    ~World();

    void update(double dt);

    void render();

    void addCell(Cell* c);
};
}

#endif //GRAE_ENGINE_WORLD_H
