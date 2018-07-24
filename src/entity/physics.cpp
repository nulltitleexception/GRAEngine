#include "physics.h"

#include "transform.h"
#include "entity.h"

namespace GRAE {
Physics::Physics() : velocity() {}

void Physics::update(double dt, Entity *parent) {
    if (parent->getComponent<AI>() != nullptr && parent->getComponent<Transform>() != nullptr) {
        parent->getComponent<Transform>()->setRot(
                MatUtil::getLookRotation(parent->getComponent<AI>()->getGoalDirection()));
    }
}

GravityPhysics::GravityPhysics() {}

void GravityPhysics::update(double dt, Entity *parent) {
    if (parent->getComponent<AI>() != nullptr && parent->getComponent<Transform>() != nullptr) {
        parent->getComponent<Transform>()->setRot(
                MatUtil::getLookRotation(parent->getComponent<AI>()->getGoalDirection()));
    }
    velocity.y -= dt;
    Transform *transform = parent->getComponent<Transform>();
    if (transform != nullptr) {
        transform->getPos() += velocity * dt;
    }
}

MovementPhysics::MovementPhysics() {}

void MovementPhysics::update(double dt, Entity *parent) {
    if (parent->getComponent<AI>() != nullptr && parent->getComponent<Transform>() != nullptr) {
        parent->getComponent<Transform>()->setRot(
                MatUtil::getLookRotation(parent->getComponent<AI>()->getGoalDirection()));
        velocity = parent->getComponent<AI>()->getGoalDirection();
    }
    Transform *transform = parent->getComponent<Transform>();
    if (transform != nullptr) {
        transform->getPos() += velocity * dt;
    }
}
}