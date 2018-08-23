#include "Environment.h"

namespace GRAE {
Environment *Environment::e = nullptr;

Environment::Environment() {
}

Environment::Environment(Gen *gen) {
    load(gen);
}

void Environment::registerListener(std::string key, std::function<void()> f){
    callbacks[key].push_back(f);
}

void Environment::load(Gen *gen, std::string prefix) {
    for (std::string key:gen->getKeys()) {
        if (gen->getFirstString(key).size()) {
            if (gen->isDouble(key)) {
                set(prefix + key, gen->getFirstDouble(key));
            } else if (gen->isInt(key)) {
                set(prefix + key, gen->getFirstInt(key));
            } else if (gen->isBool(key)) {
                set(prefix + key, gen->getFirstBool(key));
            } else {
                set(prefix + key, gen->getFirstString(key));
            }
        }
        if (gen->hasSubValues(key)) {
            load(gen->getSubValues(key), prefix + "." + key);
        }
    }
}
}