#include "type.h"
#include "engine.h"

#include "typeextend.h"
#include "typelist"

#define MAKE_MAP(VAR) \
    types[#VAR] = std::unique_ptr<Type>(new TypeImpl<VAR>(#VAR)); \
    indexedTypes[std::type_index(typeid(VAR))] = types[#VAR].get();

namespace GRAE {
TypeResolver::TypeResolver() {
    TYPELIST(MAKE_MAP);
}

void TypeResolver::extend(std::string s, GRAE::Type *type, std::type_index index) {
    types[s] = std::unique_ptr<Type>(type);
    indexedTypes[index] = types[s].get();
}

Type *TypeResolver::get(std::string s) {
    return types.at(s).get();
}

Type *TypeResolver::get(std::type_index t) {
    return indexedTypes.at(t);
}

TypeResolver TYPES;
}