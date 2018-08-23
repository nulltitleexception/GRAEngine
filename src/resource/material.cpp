#include "material.h"

namespace GRAE {
Material::Material(GRAE::Resources *res) {
    tex = res->get<Texture>();
    shader = res->get<Shader>();
    props.shininess = 0;
    props.specularity = 0;
}

Material::Material(std::string s, Resources *res, bool &success, std::string &reason) {
    Gen gen(s + ".mtrl", res, success, reason);
    tex = res->get<Texture>(gen.getFirstString("texture"));
    shader = res->get<Shader>(gen.getFirstString("shader"));
    props.shininess = gen.getFirstDouble("shininess");
    props.specularity = gen.getFirstDouble("specularity");
}

void Material::bind() {
    shader->bind();
    tex->bind();
    //send mat props to shader
    shader->setUniformFloat("shininess", (float) props.shininess);
    shader->setUniformFloat("specularity", (float) props.specularity);
}
}
