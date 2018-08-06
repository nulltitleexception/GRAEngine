#ifndef GRAE_ENGINE_TEXTMENUITEM_H
#define GRAE_ENGINE_TEXTMENUITEM_H

#include "menuitem.h"

#include <string>

namespace GRAE {
class Resources;

class Text;

class Font;

class TextMenuItem : public MenuItem {
private:
    std::string string;
    int size;
    Font *font;
    Text *text;
public:
    TextMenuItem(Resources* res, Gen* gen);

    ~TextMenuItem();

    virtual void setString(std::string s);

    virtual void setSize(int s);

    virtual void setFont(Font *f);

    virtual void setText(Text *t);

    virtual void render(int x, int y);
};
}

#endif //GRAE_ENGINE_TEXTMENUITEM_H
