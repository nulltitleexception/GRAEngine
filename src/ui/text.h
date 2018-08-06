#ifndef GRAE_ENGINE_TEXT_H
#define GRAE_ENGINE_TEXT_H

#include "menuitem.h"

#include <string>

namespace GRAE {
class Resources;

class Text2D;

class Font;

class Text : public MenuItem {
private:
    std::string string;
    int size;
    Font *font;
    Text2D *text;
public:
    Text(Resources* res, Gen* gen);

    ~Text();

    virtual void setString(std::string s);

    virtual void setSize(int s);

    virtual void setFont(Font *f);

    virtual void setText(Text2D *t);

    virtual void render(int x, int y);
};
}

#endif //GRAE_ENGINE_TEXT_H
