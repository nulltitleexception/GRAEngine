#include "menucontainer.h"

namespace GRAE {
MenuContainer::~MenuContainer() {
    for (MenuItem *child: children) {
        delete child;
    }
}
}