#ifndef GRAE_ENGINE_MENUCONTAINER_H
#define GRAE_ENGINE_MENUCONTAINER_H

#include <vector>

namespace GRAE {
class MenuItem;

class MenuContainer {
protected:
    std::vector<MenuItem *> children;
public:
    virtual ~MenuContainer();

    virtual void addSubmenu(MenuItem *item);

    virtual void renderChildren(bool drawBorders = false);

    virtual bool handleClick(int x, int y);

    virtual double getPosX();

    virtual double getPosY();

    virtual double getSizeX();

    virtual double getSizeY();
};
}

#endif //GRAE_ENGINE_MENUCONTAINER_H
