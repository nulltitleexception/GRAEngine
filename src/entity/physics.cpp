#include "physics.h"

#include "transform.h"
#include "entity.h"

namespace GRAE {
Physics::Physics() : velocity() {}

void Physics::update(double dt, Entity *parent) {}

GravityPhysics::GravityPhysics() {}

void GravityPhysics::update(double dt, Entity *parent) {
    velocity.y -= dt * 0.01;
    Transform *transform = parent->getComponent<Transform>();
    if (transform != nullptr) {
        transform->getPos() -= velocity * dt;
    }
}
}