#ifndef GRAE_ENGINE_CELL_H
#define GRAE_ENGINE_CELL_H

#include "entity/entity.h"
#include "resource/resources.h"

#include <vector>
#include <string>

namespace GRAE {
class Cell {
public:
    std::vector<Entity*> entities;
public:
    Cell();
    Cell(std::string path, Resources *res, bool& success, std::string& reason);
    ~Cell();
    void update(double dt);
    void render();
};
}

#endif //GRAE_ENGINE_CELL_H
