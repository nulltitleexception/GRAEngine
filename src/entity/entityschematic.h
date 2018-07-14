#ifndef GRAE_ENGINE_ENTITYSCHEMATIC_H
#define GRAE_ENGINE_ENTITYSCHEMATIC_H

#include "resource/resources.h"
#include "component.h"
#include "meta/meta.h"

#include <string>

namespace GRAE {
class Entity;

class EntitySchematic : Component {
    friend class Entity;
    struct TypeGen {
        Type* cast;
        Type* type;
        Gen* gen;
    };
private:
    std::unordered_map<std::type_index, Component *> ref;
    std::vector<TypeGen> init;
public:
    explicit EntitySchematic(Resources *res);

    EntitySchematic(std::string s, Resources *res, bool &success, std::string &reason);

    Entity *newInstance();

    template<typename T>
    void addComponent(T *c) {
        ref[std::type_index(typeid(T))] = c;
    }

    template<typename T>
    void addComponent() {
        init.push_back({TYPES.get<T>(), nullptr});
    }
};
}

#endif //GRAE_ENGINE_ENTITYSCHEMATIC_H
