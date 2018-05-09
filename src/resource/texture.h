#ifndef GRAE_ENGINE_TEXTURE_H
#define GRAE_ENGINE_TEXTURE_H


#include "resources.h"
#include <glad/glad.h>
#include <string>

namespace GRAE {
class Texture {
private:
    GLuint id;
    int width;
    int height;
public:
    Texture(std::string name, Resources *res);

    ~Texture();

    GLuint getID();

    int getWidth();

    int getHeight();

    void bind();

    void unbind();
};
}


#endif //GRAE_ENGINE_TEXTURE_H
