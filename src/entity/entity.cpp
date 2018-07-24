#include "entity.h"

#include "resource/gen.h"
#include "meta/type.h"

namespace GRAE {
Entity::Entity() : cell(nullptr) {}

Entity::Entity(EntitySchematic *schematic, Cell *c) : cell(c) {
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
}

void Entity::render(mat4 m) {
    if (getComponent<Transform>() != nullptr) {
        m *= getComponent<Transform>()->asMatrix();
    }
    for (auto pair : components) {
        pair.second->render(m);
    }
}

void Entity::setCell(Cell *c) { cell = c; }

Cell *Entity::getCell() { return cell; }
}
