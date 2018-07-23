#ifndef GRAE_ENGINE_AI_H
#define GRAE_ENGINE_AI_H

#include "component.h"
#include "math/vector.h"

namespace GRAE {
class AI : public Component {
public:
    AI();

    virtual void update(double dt, Entity *parent);

    virtual vec4 getGoalDirection();
};

//Builtin AIs
class SpinAI : public AI {
private:
    vec4 direction;
public:
    SpinAI();

    void update(double dt, Entity *parent) override;

    vec4 getGoalDirection() override;
};
}

#endif //GRAE_ENGINE_AI_H
