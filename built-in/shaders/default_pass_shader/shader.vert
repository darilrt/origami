#version 450

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragUV;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(std140, binding = 0) uniform Transform {
    mat4 model;
    mat4 view;
    mat4 proj;
};

void main() {
    fragNormal = normal;
    fragUV = uv;

    gl_Position = vec4(position, 1.0);
}