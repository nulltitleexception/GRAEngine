#include "menuitem.h"

#include "menucontainer.h"

namespace GRAE {
MenuItem::MenuItem(Resources *res, Gen *gen) : parent(nullptr), borders(nullptr), colorShader(nullptr) {
    colorShader = res->getFromRoot<Shader>("built_in/shader/color");
    if (gen) {
        init(gen);
    }
}

MenuItem::~MenuItem() { delete borders; }

void MenuItem::init(Gen *gen) {
    posX = gen->getDouble("alignment.x", 0);
    if (gen->getPresent("alignment.x.left")) {
        alignH = HorizontalAlignment::Left;
    } else if (gen->getPresent("alignment.x.center")) {
        alignH = HorizontalAlignment::Center;
    } else if (gen->getPresent("alignment.x.right")) {
        alignH = HorizontalAlignment::Right;
    } else if (gen->getPresent("alignment.x.relative")) {
        alignH = HorizontalAlignment::Relative;
    } else if (gen->getPresent("alignment.x.override")) {
        alignH = HorizontalAlignment::Override;
    } else {
        alignH = HorizontalAlignment::Absolute;
    }
    posY = gen->getDouble("alignment.y", 0);
    if (gen->getPresent("alignment.y.top")) {
        alignV = VerticalAlignment::Top;
    } else if (gen->getPresent("alignment.y.center")) {
        alignV = VerticalAlignment::Center;
    } else if (gen->getPresent("alignment.y.bottom")) {
        alignV = VerticalAlignment::Bottom;
    } else if (gen->getPresent("alignment.y.relative")) {
        alignV = VerticalAlignment::Relative;
    } else if (gen->getPresent("alignment.y.override")) {
        alignV = VerticalAlignment::Override;
    } else {
        alignV = VerticalAlignment::Absolute;
    }
    sizeX = gen->getDouble("size.x", 0);
    if (gen->getPresent("size.x.fill")) {
        sizeTypeX = SizeType::Fill;
    } else if (gen->getPresent("size.x.relative")) {
        sizeTypeX = SizeType::Relative;
    } else if (gen->getPresent("size.x")) {
        sizeTypeX = SizeType::Absolute;
    } else {
        sizeTypeX = SizeType::None;
    }
    sizeY = gen->getDouble("size.y", 0);
    if (gen->getPresent("size.y.fill")) {
        sizeTypeY = SizeType::Fill;
    } else if (gen->getPresent("size.y.relative")) {
        sizeTypeY = SizeType::Relative;
    } else if (gen->getPresent("size.y")) {
        sizeTypeY = SizeType::Absolute;
    } else {
        sizeTypeY = SizeType::None;
    }
}

void MenuItem::setParent(MenuContainer *p) {
    parent = p;
}

double MenuItem::getPosX() {
    if (parent == nullptr) {
        return posX;
    }
    switch (alignH) {
        case HorizontalAlignment::Left:
            return parent->getPosX();
        case HorizontalAlignment::Center:
            return parent->getPosX() + (parent->getSizeX() / 2.0) - (getSizeX() / 2.0);
        case HorizontalAlignment::Right:
            return parent->getPosX() + parent->getSizeX() - getSizeX();
        case HorizontalAlignment::Absolute:
            return parent->getPosX() + posX;
        case HorizontalAlignment::Relative:
            return parent->getPosX() + (posX * parent->getSizeX());
        case HorizontalAlignment::Override:
            return posX;
    }
}

double MenuItem::getPosY() {
    if (parent == nullptr) {
        return posY;
    }
    switch (alignV) {
        case VerticalAlignment::Top:
            return parent->getPosY();
        case VerticalAlignment::Center:
            return parent->getPosY() + (parent->getSizeY() / 2.0) - (getSizeY() / 2.0);
        case VerticalAlignment::Bottom:
            return parent->getPosY() + parent->getSizeY() - getSizeY();
        case VerticalAlignment::Absolute:
            return parent->getPosY() + posY;
        case VerticalAlignment::Relative:
            return parent->getPosY() + (posY * parent->getSizeY());
        case VerticalAlignment::Override:
            return posY;
    }
}

double MenuItem::getSizeX() {
    if (parent == nullptr) {
        return sizeX;
    }
    switch (sizeTypeX) {
        case SizeType::Fill:
            return parent->getSizeX();
        case SizeType::Absolute:
            return sizeX;
        case SizeType::Relative:
            return parent->getSizeX() * sizeX;
        case SizeType::None:
            return 0;
    }
}

double MenuItem::getSizeY() {
    if (parent == nullptr) {
        return sizeY;
    }
    switch (sizeTypeY) {
        case SizeType::Fill:
            return parent->getSizeY();
        case SizeType::Absolute:
            return sizeY;
        case SizeType::Relative:
            return parent->getSizeY() * sizeY;
        case SizeType::None:
            return 0;
    }
}

double MenuItem::getOrphanPosX() {
    switch (alignH) {
        case HorizontalAlignment::Left:
            return 0;
        case HorizontalAlignment::Center:
            return getOrphanSizeX() / -2.0;
        case HorizontalAlignment::Right:
            return -getOrphanSizeX();
        case HorizontalAlignment::Absolute:
            return posX;
        case HorizontalAlignment::Relative:
            return 0;
        case HorizontalAlignment::Override:
            return posX;
    }
}

double MenuItem::getOrphanPosY() {
    switch (alignV) {
        case VerticalAlignment::Top:
            return 0;
        case VerticalAlignment::Center:
            return getOrphanSizeY() / -2.0;
        case VerticalAlignment::Bottom:
            return -getOrphanSizeY();
        case VerticalAlignment::Absolute:
            return posY;
        case VerticalAlignment::Relative:
            return 0;
        case VerticalAlignment::Override:
            return posY;
    }
}

double MenuItem::getOrphanSizeX() {
    switch (sizeTypeX) {
        case SizeType::Fill:
            return 0;
        case SizeType::Absolute:
            return sizeX;
        case SizeType::Relative:
            return 0;
        case SizeType::None:
            return 0;
    }
}

double MenuItem::getOrphanSizeY() {
    switch (sizeTypeY) {
        case SizeType::Fill:
            return 0;
        case SizeType::Absolute:
            return sizeY;
        case SizeType::Relative:
            return 0;
        case SizeType::None:
            return 0;
    }
}

void MenuItem::render(bool drawBorders) {
    if (drawBorders) {
        renderBorder();
    }
}

void MenuItem::renderBorder() {
    if (!borders) {
        borders = Mesh2D::createBorders(getPosX(), getPosY(), getPosX() + getSizeX(), getPosY() + getSizeY());
    }
    colorShader->bind();
    colorShader->setUniformVec4("color", vec4(1, 1, 1, 1));
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(mat4(1));
    borders->renderWireframe();
}
}