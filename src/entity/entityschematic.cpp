#include "entityschematic.h"

#include "entity.h"
#include "resource/config.h"

namespace GRAE {
EntitySchematic::EntitySchematic() {}

EntitySchematic::EntitySchematic(Resources *res) {}

EntitySchematic::EntitySchematic(std::string s, Resources *res, bool &success, std::string &reason) {
    Config *cfg = res->getFromRoot<Config>(s + ".ent");
    std::vector<std::string> keys = cfg->getKeys();
    for (auto key : keys) {
        std::string val = cfg->getString(key);
        Type *type = TYPES.get(key);
        if (val.size()) {
            ref[type->getIndex()] = (Component *) type->load(res, val);
        } else {
            init.push_back(type);
        }
    }
    success = true;
}

Entity *EntitySchematic::newInstance() {
    return new Entity(this);
}
}