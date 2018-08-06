#include "menu.h"

#include "system/log.h"

namespace GRAE {
Menu::Menu() {}

Menu::Menu(Resources *res) {}

Menu::Menu(std::string s, Resources *res, bool &success, std::string &reason) {
    Gen gen(s + ".mnu", res, success, reason);
    init(&gen);
    for (const std::string &key : gen.getKeys()) {
        Gen *subvalues = gen.getSubValues(key);
        if (subvalues != nullptr) {
            addSubmenu((MenuItem *) TYPES.get(gen.getString(key))->construct(res, subvalues));
        }
    }
}

void Menu::render(int x, int y) {
    MenuItem::render(x, y);
    MenuContainer::renderChildren(x, y);
}
}