#ifndef GRAE_ENGINE_ENVIRONMENT_H
#define GRAE_ENGINE_ENVIRONMENT_H

#include "variables.h"

#include <string>

namespace GRAE {
class Environment {
private:
    VariableSet *vars;
public:
    Environment(VariableSet *v);

    std::string execute(std::string command);
};
}

#endif //GRAE_ENGINE_ENVIRONMENT_H
