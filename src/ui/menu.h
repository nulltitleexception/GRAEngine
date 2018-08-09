#ifndef GRAE_ENGINE_MENU_H
#define GRAE_ENGINE_MENU_H

#include "menucontainer.h"
#include "menuitem.h"
#include "meta/type.h"

namespace GRAE {
class Menu : public MenuContainer, public MenuItem {
public:
    Menu(Resources *res);

    Menu(Resources *res, Gen *gen);

    Menu(std::string s, Resources *res, bool &success, std::string &reason);

    virtual ~Menu();

    virtual void init(Resources *res, Gen *gen);

    virtual void render(bool drawBorders = false);

    virtual double getPosX();

    virtual double getPosY();

    virtual double getSizeX();

    virtual double getSizeY();

    virtual double getOrphanSizeX();

    virtual double getOrphanSizeY();
};
}

#endif //GRAE_ENGINE_MENU_H
