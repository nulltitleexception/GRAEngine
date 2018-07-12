#ifndef GRAE_ENGINE_MENU_H
#define GRAE_ENGINE_MENU_H

namespace GRAE {
class Menu {
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
    Num pos;
    Num size;
public:
    Menu();
    void render();
};
}

#endif //GRAE_ENGINE_MENU_H
