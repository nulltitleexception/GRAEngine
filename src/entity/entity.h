#ifndef GRAE_ENGINE_ENTITY_H
#define GRAE_ENGINE_ENTITY_H

#include "component.h"
#include "model.h"
#include "transform.h"
#include "entityschematic.h"
#include "ai.h"
#include "physics.h"

#include "resource/resources.h"
#include "math/math.h"
#include "world/cell.h"
#include "world/world.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>

namespace GRAE {
class Cell;

class Entity : Component {
private:
    std::unordered_map<std::type_index, Component *> components;
    std::vector<std::unique_ptr<Component>> owned;
    Cell *cell;
public:
    Entity();

    Entity(EntitySchematic *schematic, Cell* c);

    template<typename T>
    T *getComponent() {
        if (components.count(std::type_index(typeid(T)))) {
            return (T *) components[std::type_index(typeid(T))];
        } else {
            return nullptr;
        }
    }

    template<typename T>
    void addComponent(T *c) {
        components[std::type_index(typeid(T))] = c;
    }

    template<typename T>
    void addComponent() {
        T *t = new T();
        owned.push_back(std::unique_ptr<Component>(t));
        addComponent<T>(t);
    }

    void update(double dt);

    void render(mat4 m = mat4());

    void setCell(Cell *c);

    Cell *getCell();
};
}

#endif //GRAE_ENGINE_ENTITY_H
