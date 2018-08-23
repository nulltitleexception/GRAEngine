#include "entityschematic.h"

#include "entity.h"
#include "resource/gen.h"

namespace GRAE {
EntitySchematic::EntitySchematic(Resources *res) {}

EntitySchematic::EntitySchematic(std::string s, Resources *res, bool &success, std::string &reason) {
    Gen *gen = res->getFromRoot<Gen>(s + ".ent");
    std::vector<std::string> keys = gen->getKeys();
    for (auto key : keys) {
        std::string val = gen->getFirstString(key);
        Type *type = TYPES.get(key);
        if (gen->getSubValues(key) || !val.size()) {
            Type *inner = val.size() ? TYPES.get(val) : type;
            init.push_back({type, inner, gen->getSubValues(key)});
        } else {
            ref[type->getIndex()] = (Component *) type->load(res, val);
        }
    }
    success = true;
}

Entity *EntitySchematic::newInstance(Cell* c) {
    return new Entity(this, c);
}
}