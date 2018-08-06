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
    if (!types.count(s)) {
        log->err << "Type \"" << s << "\" does not exist or is not registered.\n"
                 << "Types must curently be registered at compile time.\n"
                 << "Register a new type \"TypeName\" by placing the line:\n"
                 << "\"ADDTYPE(TypeName)\"\n"
                 << " anywhere before the Resource Handler is instantiated.\n"
                 << "(Reccomended position is at the beginning of the main() function)";
        return nullptr;
    }
    return types.at(s).get();
}

Type *TypeResolver::get(std::type_index t) {
    if (!indexedTypes.count(t)) {
        log->err << "Type \"" << t.name() << "\" does not exist or is not registered.\n"
                 << "Types must curently be registered at compile time.\n"
                 << "Register a new type \"TypeName\" by placing the line:\n"
                 << "\"ADDTYPE(TypeName)\"\n"
                 << " anywhere before the Resource Handler is instantiated.\n"
                 << "(Reccomended position is at the beginning of the main() function)";
        return nullptr;
    }
    return indexedTypes.at(t);
}

TypeResolver TYPES;
}