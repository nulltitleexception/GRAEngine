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

    virtual ~Text();

    virtual void setString(std::string s);

    virtual void setSize(int s);

    virtual void setFont(Font *f);

    virtual void setText(Text2D *t);

    virtual double getSizeX();

    virtual double getSizeY();

    virtual double getOrphanSizeX();

    virtual double getOrphanSizeY();

    virtual void render(bool drawBorders = false);
};
}

#endif //GRAE_ENGINE_TEXT_H
