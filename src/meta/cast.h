#ifndef GRAE_ENGINE_CAST_H
#define GRAE_ENGINE_CAST_H

#include <typeindex>
#include <unordered_map>
#include <memory>

namespace GRAE {
class InnerCaster {
public:
    virtual ~InnerCaster() {}

    virtual void *cast(std::type_index index, void *p)=0;
};

class TypeCaster {
private:
    std::unordered_map<std::type_index, std::unique_ptr<InnerCaster>> indexedCasters;
public:
    TypeCaster();

    void *cast(std::type_index to, std::type_index from, void *p);

    template<typename C>
    C*cast(std::type_index from, void* p){
        return (C*)cast(std::type_index(typeid(C)),from,p);
    };

    template<typename C, typename P>
    C*cast(void* p){
        return cast<C>(std::type_index(typeid(P)), p);
    };
};

extern TypeCaster CAST;
}

#endif //GRAE_ENGINE_CAST_H