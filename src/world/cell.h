#ifndef GRAE_ENGINE_CELL_H
#define GRAE_ENGINE_CELL_H

#include "entity/entity.h"
#include "resource/resources.h"

#include <vector>
#include <string>

namespace GRAE {
class Cell {
private:
    std::vector<Entity*> entities;
public:
    Cell();
    Cell(std::string s, Resources* res);
    ~Cell();
    void update(double dt);
    void render();
};
}

#endif //GRAE_ENGINE_CELL_H
