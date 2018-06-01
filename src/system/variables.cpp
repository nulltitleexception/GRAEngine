#include "variables.h"

namespace GRAE {
VariableSet::VariableSet() {}

VariableSet::~VariableSet() {
    for (auto pair = values.begin(); pair != values.end(); ++pair) {
        delete pair->second;
    }
}
}