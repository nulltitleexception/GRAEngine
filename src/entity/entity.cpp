#include "entity.h"

#include "resource/gen.h"
#include "meta/type.h"

namespace GRAE {
Entity::Entity() {}

Entity::Entity(EntitySchematic *schematic) {
    for (auto pair : schematic->ref) {
        components[pair.first] = (Component *) pair.second;
    }
    for (EntitySchematic::TypeGen typegen : schematic->init) {
        void *t = ((typegen.gen && typegen.gen->size()) ? typegen.type->construct(typegen.gen)
                                                        : typegen.type->construct());
        owned.push_back(std::unique_ptr<Component>((Component *) t));
        components[typegen.cast->getIndex()] = (Component *) t;
    }
}

void Entity::update(double dt) {
    for (auto pair : components) {
        pair.second->update(dt, this);
    }
    if (getComponent<AI>() != nullptr && getComponent<Transform>() != nullptr) {
        double SPEED = dt;
        getComponent<Transform>()->getPos() += getComponent<AI>()->getGoalDirection() * SPEED;
        getComponent<Transform>()->setRot(MatUtil::getLookRotation(getComponent<AI>()->getGoalDirection()));
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
