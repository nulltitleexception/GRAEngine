#include "menuitem.h"

namespace GRAE {
MenuItem::MenuItem() : borders(nullptr) {}

MenuItem::MenuItem(Gen *gen) : borders(nullptr) {
    init(gen);
}

MenuItem::~MenuItem() { delete borders; }

void MenuItem::init(Gen *gen) {}

void MenuItem::render(int x, int y) {

}

void MenuItem::renderBorder(int x, int y) {
    if (!borders) {
        borders = Mesh2D::createBox(posX.abs, posY.abs, posX.abs + size.abs, posY.abs + size.abs);
    }
    log->err << "ERROR";
    //borders->render();
}
}