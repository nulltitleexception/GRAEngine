#ifndef GRAE_ENGINE_TYPE_H
#define GRAE_ENGINE_TYPE_H

#include <typeindex>
#include <unordered_map>
#include <memory>

namespace GRAE {
class Resources;

class Gen;

enum class TYPE_ID {

};

class Type {
public:
    virtual void *construct()=0;

    virtual void *construct(Gen *gen)=0;

    virtual void *load(Resources *res, std::string name)=0;

    virtual std::type_index getIndex()=0;

    virtual std::string getName()=0;
};

class TypeResolver {
private:
    std::unordered_map<std::string, std::unique_ptr<Type>> types;
    std::unordered_map<std::type_index, Type *> indexedTypes;
public:
    TypeResolver();

    void extend(std::string s, Type* type, std::type_index index);

    Type *get(std::string s);

    Type *get(std::type_index t);

    template<typename T>
    Type *get() {
        return get(std::type_index(typeid(T)));
    }
};

extern TypeResolver TYPES;
}

#endif //GRAE_ENGINE_TYPE_H
