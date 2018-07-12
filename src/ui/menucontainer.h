#ifndef GRAE_ENGINE_MENUCONTAINER_H
#define GRAE_ENGINE_MENUCONTAINER_H

namespace GRAE {
class Menu;

class MenuContainer {
    MenuContainer();

    void addSubmenu();

    void renderChildren();

    bool handleClick(int x, int y);
};
}

#endif //GRAE_ENGINE_MENUCONTAINER_H
