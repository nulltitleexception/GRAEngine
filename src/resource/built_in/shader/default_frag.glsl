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
    vec3 normal = normalize(pass_normal);
    vec4 texCol = texture(tex, pass_UV);
    vec3 lightVec = normalize(vec3(1,1,1));
    vec3 viewVec = vec3(0,0,1);
    vec3 halfAngle = normalize((lightVec+viewVec)/2);
    float spec_light = dot((vec4(normal,0)), vec4(halfAngle, 0));
    spec_light = max(spec_light, 0);
    spec_light = pow(spec_light, specularity)*shininess;
    float ambient_light = 0.4;
    float diffuse_light = (1-ambient_light);
    diffuse_light *= dot(lightVec,normal);
    vec4 ambient = texCol * vec4(vec3(ambient_light), 1);
    vec4 diffuse = texCol * vec4(vec3(diffuse_light), 0);
    vec4 specular = vec4(vec3(spec_light), 0);
    fragColor = specular + diffuse + ambient;
}
)***"