#include "texture.h"

#include "system/log.h"

#include "IL/il.h"
#include <glad/glad.h>

namespace GRAE {
Texture::Texture(Resources *res) {
    static bool ilInited = false;
    if (!ilInited) {
        ilInited = true;
        ilInit();
    }
    width = 1;
    height = 1;
    glGenTextures(1, &id);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char magenta[] = {255, 0, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &magenta[0]);
}

Texture::Texture(std::string name, Resources *res, bool &success, std::string &reason) {
    static bool ilInited = false;
    if (!ilInited) {
        ilInited = true;
        ilInit();
    }
    ILuint ilid;
    ilGenImages(1, &ilid);
    ilBindImage(ilid);
    if (ilLoadImage((name + ".png").c_str()) == IL_FALSE) {
        success = false;
    } else {
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        glGenTextures(1, &id);
        bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
        ilDeleteImages(1, &ilid);
        success = true;
    }
}

Texture::~Texture() {
    bind();
    glDeleteTextures(1, &id);
    unbind();
    id = 0;
}

GLuint Texture::getID() {
    return id;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
}