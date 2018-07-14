#ifndef GRAE_ENGINE_ENTITY_H
#define GRAE_ENGINE_ENTITY_H

#include "component.h"
#include "model.h"
#include "transform.h"
#include "entityschematic.h"
#include "ai.h"

#include "resource/resources.h"
#include "math/math.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>

namespace GRAE {
class Entity : Component {
private:
    std::unordered_map<std::type_index, Component *> components;
    std::vector<std::unique_ptr<Component>> owned;
public:
    Entity();

    explicit Entity(EntitySchematic *schematic);

    template<typename T>
    T *getComponent() {
        return (T *) components[std::type_index(typeid(T))];
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
};
}

#endif //GRAE_ENGINE_ENTITY_H
