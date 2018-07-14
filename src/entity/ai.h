#ifndef GRAE_ENGINE_AI_H
#define GRAE_ENGINE_AI_H

#include "component.h"
#include "math/vector.h"

namespace GRAE {
class AI : public Component {
    virtual AI() {

    }

    virtual void update(double dt, Entity *parent) {}

    virtual vec4 getGoalDirection() { return vec4(); }
};
}

#endif //GRAE_ENGINE_AI_H
