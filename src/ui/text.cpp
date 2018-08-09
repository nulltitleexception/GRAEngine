#include "text.h"

#include "resource/text2d.h"
#include "resource/font.h"

namespace GRAE {
Text::Text(Resources *res, Gen *gen) : MenuItem(res, gen) {
    string = gen->getString("string", "");
    size = gen->getInt("size", 12);
    font = res->get<Font>(gen->getString("font", ""));
    text = font->getText(string, size);
}

Text::~Text() {
    delete text;
}

void Text::setString(std::string s) {
    string = s;
    if (font != nullptr) {
        setText(font->getText(string, size));
    }
}

void Text::setSize(int s) {
    size = s;
    if (font != nullptr) {
        setText(font->getText(string, size));
    }
}

void Text::setFont(Font *f) {
    font = f;
    setText(font->getText(string, size));
}

void Text::setText(Text2D *t) {
    delete text;
    text = t;
}

void Text::render(bool drawBorders) {
    MenuItem::render(drawBorders);
    if (text != nullptr) {
        text->render(MatUtil::translation(getPosX(), getPosY(), 0));
    }
}

double Text::getSizeX() {
    return text->getWidth();
}

double Text::getSizeY() {
    return text->getHeight();
}

double Text::getOrphanSizeX() {
    return text->getWidth();
}

double Text::getOrphanSizeY() {
    return text->getHeight();
}
}