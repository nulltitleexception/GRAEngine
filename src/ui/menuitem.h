#ifndef GRAE_ENGINE_MENUITEM_H
#define GRAE_ENGINE_MENUITEM_H

#include <resource/mesh.h>

namespace GRAE {
class Resources;

class Gen;

class MenuItem {
public:
    enum class HorizontalAlignment {
        Left,
        Center,
        Right,
        Absolute,
        Relative
    };
    enum class VerticalAlignment {
        Top,
        Center,
        Bottom,
        Absolute,
        Relative
    };
    enum class SizeType {
        None,
        Fill,
        Absolute,
        Relative
    };
    union Num {
        float rel;
        int abs;
    };
private:
    HorizontalAlignment alighH;
    VerticalAlignment alignV;
    SizeType sizeType;
    Num posX;
    Num posY;
    Num size;
    Mesh2D* borders;
public:
    MenuItem();

    MenuItem(Gen * gen);

    virtual ~MenuItem();

    void init(Gen* gen);

    virtual void render(int x, int y);

    virtual void renderBorder(int x, int y);
};
}

#endif //GRAE_ENGINE_MENUITEM_H
