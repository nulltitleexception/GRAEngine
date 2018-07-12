R"***(
#version 430 core

layout(location = 1) in vec3 normal;
layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 UV;

layout (location = 3) uniform mat4 model;
layout (location = 4) uniform mat4 entity;
layout (location = 5) uniform mat4 view;
layout (location = 6) uniform mat4 projection;

out vec3 pass_normal;
out vec3 pass_pos;
out vec2 pass_UV;
out mat4 pass_view;

void main(){
    pass_pos = (entity * vec4(pos, 1.0)).xyz;
    gl_Position = projection * view * entity * vec4(pos, 1.0);
    pass_normal = (entity * vec4(normal, 0)).xyz;
    pass_UV = UV;
    pass_view = view;
}
)***"