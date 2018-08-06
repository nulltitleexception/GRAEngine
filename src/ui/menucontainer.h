#ifndef GRAE_ENGINE_MENUCONTAINER_H
#define GRAE_ENGINE_MENUCONTAINER_H

#include "menuitem.h"
#include <vector>

namespace GRAE {
class MenuContainer {
private:
    std::vector<MenuItem *> children;
public:
    virtual ~MenuContainer();

    virtual void addSubmenu(MenuItem *item) {
        children.push_back(item);
    }

    virtual void renderChildren(int x, int y) {
        for (MenuItem *child : children) {
            child->render(x, y);
        }
    }

    virtual bool handleClick(int x, int y) {
        for (MenuItem *child : children) {
            //pass click
        }
    };
};
}

#endif //GRAE_ENGINE_MENUCONTAINER_H
