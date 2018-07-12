R"***(
#version 430 core

in vec3 pass_pos;
in vec3 pass_normal;
in vec2 pass_UV;
in mat4 pass_view;

out vec4 fragColor;

uniform sampler2D tex;

uniform float shininess;
uniform float specularity;

uniform vec4 color;

void main() {
    fragColor = color;
}
)***"