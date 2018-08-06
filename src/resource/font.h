#ifndef GRAE_ENGINE_FONT_H
#define GRAE_ENGINE_FONT_H

#include "resources.h"
#include "texture.h"
#include "shader.h"
#include "text2d.h"

#include <string>

namespace GRAE {
class FontData {
private:
    int maxSize;
    int num;
    int *data;
public:
    FontData(Resources *res);

    FontData(std::string path, Resources *res, bool &success, std::string &reason);

    ~FontData();

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
    Font(Resources *res);

    Font(std::string path, Resources *res, bool &success, std::string &reason);

    Text2D *getText(std::string t, int size = 12);
};
}


#endif //GRAE_ENGINE_FONT_H
