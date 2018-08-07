#include "menucontainer.h"

#include "menuitem.h"

namespace GRAE {
MenuContainer::~MenuContainer() {
}

void MenuContainer::addSubmenu(MenuItem *item) {
    children.push_back(item);
    item->setParent(this);
}

void MenuContainer::renderChildren(bool drawBorders) {
    for (MenuItem *child : children) {
        child->render(drawBorders);
    }
}

bool MenuContainer::handleClick(int x, int y) {
    for (MenuItem *child : children) {
        //pass click
    }
};

double MenuContainer::getPosX() {
    return 0;
}

double MenuContainer::getPosY() {
    return 0;
}

double MenuContainer::getSizeX() {
    return 0;
}

double MenuContainer::getSizeY() {
    return 0;
}
}