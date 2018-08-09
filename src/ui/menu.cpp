#include "menu.h"

#include "system/log.h"

#include "meta/cast.h"

namespace GRAE {
Menu::Menu(Resources *res) : MenuItem(res, nullptr) {}

Menu::Menu(Resources *res, Gen *gen) : MenuItem(res, gen) {
    init(res, gen);
}

Menu::Menu(std::string s, Resources *res, bool &success, std::string &reason) : MenuItem(res, nullptr) {
    Gen gen(s + ".mnu", res, success, reason);
    MenuItem::init(&gen);
    init(res, &gen);
}

Menu::~Menu() {
    for (MenuItem *child : children) {
        delete child;
    }
}

void Menu::init(Resources *res, Gen *gen) {
    for (std::string key : gen->getKeys()) {
        Gen *subvalues = gen->getSubValues(key);
        if (gen->getString(key).size() && subvalues != nullptr) {
            Type *type = TYPES.get(gen->getString(key));
            addSubmenu(CAST.cast<MenuItem>(type->getIndex(), type->construct(res, subvalues)));
        }
    }
}

void Menu::render(bool drawBorders) {
    MenuItem::render(drawBorders);
    MenuContainer::renderChildren(drawBorders);
}

double Menu::getPosX() {
    return MenuItem::getPosX();
}

double Menu::getPosY() {
    return MenuItem::getPosY();
}

double Menu::getSizeX() {
    return MenuItem::getSizeX();
}

double Menu::getSizeY() {
    return MenuItem::getSizeY();
}
}