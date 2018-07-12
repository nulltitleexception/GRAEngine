#include "type.h"

#include "engine.h"

#define TYPELIST(OP) \
    OP(Entity) \
    OP(Model) \
    OP(Transform)

#define MAKE_MAP(VAR) \
    types[#VAR] = std::unique_ptr<Type>(new TypeImpl<VAR>(#VAR)); \
    indexedTypes[std::type_index(typeid(VAR))] = types[#VAR].get();

namespace GRAE {
template<typename T>
class TypeImpl : public Type {
private:
    std::string name;
public:
    TypeImpl(std::string s) : name(s) {}

private:
    struct general_ {
    };
    struct special_ : general_ {
    };
    template<typename>
    struct int_ {
        typedef int type;
    };

    template<typename U, typename int_<decltype(U())>::type = 0>
    void *constructImpl(special_) {
        return new U();
    }

    template<typename U>
    void *constructImpl(general_) {
        log->err << "invalid constructImpl called";
        return nullptr;
    }

    template<typename U, typename int_<decltype(U("", std::declval<Resources *>(),
                                                  std::declval<bool &>(), std::declval<std::string &>()))>::type = 0>
    void *loadImpl(Resources *res, std::string name, special_) {
        return res->get<U>(name);
    }

    template<typename U>
    void *loadImpl(Resources *res, std::string name, general_) {
        log->err << "invalid loadImpl called";
        return nullptr;
    }

public:
    void *construct() override {
        return constructImpl<T>(special_());
    }

    void *load(Resources *res, std::string name) override {
        return loadImpl<T>(res, name, special_());
    }

    std::type_index getIndex() override {
        return std::type_index(typeid(T));
    }

    std::string getName() override {
        return name;
    }
};


TypeResolver::TypeResolver() {
    TYPELIST(MAKE_MAP);
}

Type *TypeResolver::get(std::string s) {
    return types.at(s).get();
}

Type *TypeResolver::get(std::type_index t) {
    return indexedTypes.at(t);
}

TypeResolver TYPES;
}