#include "entity.h"

#include "resource/config.h"
#include "meta/type.h"

namespace GRAE {
Entity::Entity() {}

Entity::Entity(EntitySchematic *schematic) {
    for (auto pair : schematic->ref) {
        components[pair.first] = (Component *) pair.second;
    }
    for (Type *type :schematic->init) {
        void *t = type->construct();
        owned.push_back(std::unique_ptr<Component>((Component *) t));
        components[type->getIndex()] = (Component *) t;
    }
}

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
