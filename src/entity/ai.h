#ifndef GRAE_ENGINE_AI_H
#define GRAE_ENGINE_AI_H

#include "component.h"
#include "math/vector.h"

namespace GRAE {
class AI : public Component {
public:
    AI() {

    }

    virtual void update(double dt, Entity *parent) {}

    virtual vec4 getGoalDirection() { return vec4(); }
};

//Builtin AIs
class SpinAI : public AI {
private:
    vec4 direction;
public:
    SpinAI() {}

    void update(double dt, Entity *parent) override {
        direction += direction.cross(vec4(0, 1, 0, 0)) * 0.01;
        direction.normalize();
    }

    vec4 getGoalDirection() override {
        return direction;
    }
};
}

#endif //GRAE_ENGINE_AI_H
