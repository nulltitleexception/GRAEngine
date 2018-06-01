#include "entity.h"

namespace GRAE {
    Entity::Entity() {}

    void Entity::update(double dt) {
        for (auto pair : components) {
            pair.second->update(dt, this);
        }
    }

    void Entity::render(mat4 m) {
        if (getComponent<Transform>() != nullptr) {
            m *= getComponent<Transform>()->asMatrix();
        }
        for (auto pair : components) {
            pair.second->render(m);
        }
    }
}
