#include "entity.h"

namespace GRAE {
    Entity::Entity() {}

    template<typename T>
    T *Entity::getComponent() {
        return (T *) components[std::type_index(typeid(T))];
    }

    template<typename T>
    void Entity::addComponent(T *c) {
        components[std::type_index(typeid(T))] = c;
    }

    void Entity::update(double dt) {
        for (auto pair : components) {
            pair.second->update(dt, this);
        }
    }

    void Entity::draw(mat4 m) {
        if (getComponent<Transform>() != nullptr) {
            m *= getComponent<Transform>()->asMatrix();
        }
        for (auto pair : components) {
            pair.second->draw(m);
        }
    }
}
