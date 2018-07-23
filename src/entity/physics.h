#ifndef GRAE_ENGINE_PHYSICS_H
#define GRAE_ENGINE_PHYSICS_H

#include "component.h"

namespace GRAE {
class Physics : public Component {
protected:
    vec4 velocity;
public:
    Physics();

    virtual void update(double dt, Entity *parent);
};

//Builtin Physics
class GravityPhysics : public Physics {
public:
    GravityPhysics();

    void update(double dt, Entity *parent) override;
};
}

#endif //GRAE_ENGINE_PHYSICS_H
