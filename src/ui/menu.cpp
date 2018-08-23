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
        if (gen->getFirstString(key).size() && subvalues != nullptr) {
            if (gen->getFirstString(key) == "load") {
                addSubmenu(res->getInstance<Menu>(subvalues->getKeys()[0]));
            } else {
                Type *type = TYPES.get(gen->getFirstString(key));
                addSubmenu(CAST.cast<MenuItem>(type->getIndex(), type->construct(res, subvalues)));
            }
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
    if (parent == nullptr && sizeTypeX != SizeType::None) {
        return sizeX;
    }
    switch (sizeTypeX) {
        case SizeType::Fill:
            return parent->getSizeX();
        case SizeType::Absolute:
            return sizeX;
        case SizeType::Relative:
            return parent->getSizeX() * sizeX;
        case SizeType::None: {
            double ret = 0;
            for (MenuItem *child : children) {
                double s = child->getOrphanSizeX();
                ret = ret > s ? ret : s;
            }
            return ret;
        }
    }
}

double Menu::getSizeY() {
    if (parent == nullptr && sizeTypeY != SizeType::None) {
        return sizeY;
    }
    switch (sizeTypeY) {
        case SizeType::Fill:
            return parent->getSizeY();
        case SizeType::Absolute:
            return sizeY;
        case SizeType::Relative:
            return parent->getSizeY() * sizeY;
        case SizeType::None: {
            double ret = 0;
            for (MenuItem *child : children) {
                double s = child->getOrphanSizeY();
                ret = ret > s ? ret : s;
            }
            return ret;
        }
    }
}

double Menu::getOrphanSizeX() {
    switch (sizeTypeX) {
        case SizeType::Absolute:
            return sizeX;
        case SizeType::Relative:
            return 0;
        case SizeType::Fill:
        case SizeType::None: {
            double ret = 0;
            for (MenuItem *child : children) {
                double s = child->getOrphanSizeX();
                ret = ret > s ? ret : s;
            }
            return ret;
        }
    }
}

double Menu::getOrphanSizeY() {
    switch (sizeTypeY) {
        case SizeType::Absolute:
            return sizeY;
        case SizeType::Relative:
            return 0;
        case SizeType::Fill:
        case SizeType::None: {
            double ret = 0;
            for (MenuItem *child : children) {
                double s = child->getOrphanSizeY();
                ret = ret > s ? ret : s;
            }
            return ret;
        }
    }
}
}