#ifndef GRAE_ENGINE_ENTITY_H
#define GRAE_ENGINE_ENTITY_H

#include "transform.h"
#include "model.h"

#include "component.h"
#include "math/math.h"
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace GRAE {
class Entity : Component {
private:
    std::unordered_map<std::type_index, Component *> components;
public:
    Entity();

    template<typename T>
    T *getComponent(){
        return (T *) components[std::type_index(typeid(T))];
    }

    template<typename T>
    void addComponent(T *c){
        components[std::type_index(typeid(T))] = c;
    }

    void update(double dt);

    void render(mat4 m = mat4());
};
}

#endif //GRAE_ENGINE_ENTITY_H
