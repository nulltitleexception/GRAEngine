#include "text.h"

#include "resource/text2d.h"
#include "resource/font.h"

namespace GRAE {
Text::Text(Resources *res, Gen *gen) : MenuItem(gen), string(""), size(0), font(nullptr),
                                                       text(nullptr) {
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

void Text::render(int x, int y) {
    if (text != nullptr) {
        text->render();
    }
}
}