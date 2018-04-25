#ifndef GRAE_ENGINE_COMPONENT_H
#define GRAE_ENGINE_COMPONENT_H

#include "math/math.h"

namespace GRAE {
class Entity;

class Component {
public:
    virtual void update(double dt, Entity* parent){}
    virtual void draw(mat4 m){}
};
}


#endif //GRAE_ENGINE_COMPONENT_H
