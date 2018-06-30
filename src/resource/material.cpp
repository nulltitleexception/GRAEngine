#include "material.h"

namespace GRAE {
Material::Material(std::string s, Resources *res, bool& success, std::string& reason) {
    Config cfg(s + ".mtrl", res, success, reason);
    tex = res->get<Texture>(cfg.getString("texture"));
    shader = res->get<Shader>(cfg.getString("shader"));
    props.shininess = cfg.getDouble("shininess");
    props.specularity = cfg.getDouble("specularity");
}

void Material::bind() {
    shader->bind();
    tex->bind();
    //send mat props to shader
    shader->setUniformFloat("shininess", (float) props.shininess);
    shader->setUniformFloat("specularity", (float) props.specularity);
}
}
