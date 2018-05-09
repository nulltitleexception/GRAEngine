#ifndef GRAE_ENGINE_FONT_H
#define GRAE_ENGINE_FONT_H

#include "resources.h"
#include "texture.h"
#include "ui/ui.h"

#include <string>

namespace GRAE {
class FontData {
private:
    int maxSize;
    int num;
    int *data;
public:
    FontData(std::string path, Resources *res);

    int getMaxSize();

    int getNum();

    int *getPositions(int size);

    int getTop(int size);

    int getBottom(int size);
};

class Font {
private:
    Texture *texture;
    Shader *shader;
    FontData *data;
public:
    Font(std::string path, Resources *res);

    Text *getText(std::string t, int size = 12);
};
}


#endif //GRAE_ENGINE_FONT_H
