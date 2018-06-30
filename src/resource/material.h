#ifndef GRAE_ENGINE_MATERIAL_H
#define GRAE_ENGINE_MATERIAL_H

#include "texture.h"
#include "shader.h"
#include "resources.h"
#include "config.h"

namespace GRAE {
struct MaterialProperties {
    double shininess;
    double specularity;
};

class Material {
private:
    Texture *tex;
    Shader *shader;
    MaterialProperties props;
public:
    Material(std::string s, Resources *res, bool& success, std::string& reason);

    void bind();
};
}


#endif //GRAE_ENGINE_MATERIAL_H
