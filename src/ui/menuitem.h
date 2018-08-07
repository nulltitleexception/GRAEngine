#ifndef GRAE_ENGINE_MENUITEM_H
#define GRAE_ENGINE_MENUITEM_H

#include "resource/shader.h"
#include "resource/mesh.h"
#include "resource/gen.h"

namespace GRAE {
class Resources;

class MenuContainer;

class MenuItem {
public:
    enum class HorizontalAlignment {
        Left,
        Center,
        Right,
        Absolute, //number of pixels relative to origin of parent
        Relative, //ratio of parent's size
        Override //number of pixels relative to top left of window
    };
    enum class VerticalAlignment {
        Top,
        Center,
        Bottom,
        Absolute, //number of pixels relative to origin of parent
        Relative, //ratio of parent's size
        Override //number of pixels relative to top left of window
    };
    enum class SizeType {
        None,
        Fill,
        Absolute,
        Relative
    };
protected:
    HorizontalAlignment alignH;
    VerticalAlignment alignV;
    SizeType sizeTypeX, sizeTypeY;
    double posX, posY;
    double sizeX, sizeY;
    MenuContainer *parent;
private:
    Mesh2D *borders;
    Shader *colorShader;
public:
    MenuItem(Resources *res, Gen *gen);

    virtual ~MenuItem();

    void init(Gen *gen);

    void setParent(MenuContainer *p);

    virtual double getPosX();

    virtual double getPosY();

    virtual double getSizeX();

    virtual double getSizeY();

    virtual void render(bool drawBorder = false);

    virtual void renderBorder();
};
}

#endif //GRAE_ENGINE_MENUITEM_H
