#ifndef GRAE_ENGINE_MENU_H
#define GRAE_ENGINE_MENU_H

#include "menucontainer.h"
#include "menuitem.h"
#include "meta/type.h"

namespace GRAE {
class Menu : public MenuContainer, public MenuItem {
public:
    Menu();

    Menu(Resources* res);

    Menu(std::string s, Resources *res, bool &success, std::string &reason);

    virtual void render(int x, int y);
};
}

#endif //GRAE_ENGINE_MENU_H
