#ifndef GRAE_ENGINE_TEXTURE_H
#define GRAE_ENGINE_TEXTURE_H

#include "resources.h"
#include <string>

namespace GRAE {
class Texture {
private:
    unsigned int id;
    int width;
    int height;
public:
    explicit Texture(Resources *res);

    Texture(std::string name, Resources *res, bool &success, std::string &reason);

    ~Texture();

    unsigned int getID();

    int getWidth();

    int getHeight();

    void bind();

    void unbind();
};
}


#endif //GRAE_ENGINE_TEXTURE_H
