#include "textmenuitem.h"

#include "text.h"
#include "resource/font.h"

namespace GRAE {
TextMenuItem::TextMenuItem(Resources *res, Gen *gen) : MenuItem(gen), string(""), size(0), font(nullptr),
                                                       text(nullptr) {
    string = gen->getString("string", "");
    size = gen->getInt("size", 12);
    font = res->get<Font>(gen->getString("font", ""));
    text = font->getText(string, size);
}

TextMenuItem::~TextMenuItem() {
    delete text;
}

void TextMenuItem::setString(std::string s) {
    string = s;
    if (font != nullptr) {
        setText(font->getText(string, size));
    }
}

void TextMenuItem::setSize(int s) {
    size = s;
    if (font != nullptr) {
        setText(font->getText(string, size));
    }
}

void TextMenuItem::setFont(Font *f) {
    font = f;
    setText(font->getText(string, size));
}

void TextMenuItem::setText(Text *t) {
    delete text;
    text = t;
}

void TextMenuItem::render(int x, int y) {
    if (text != nullptr) {
        text->render();
    }
}
}