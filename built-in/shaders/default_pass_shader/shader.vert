#version 450

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragUV;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

void main() {
    fragNormal = normal;
    fragUV = uv;

    gl_Position = vec4(position * 2.0, 1.0);
}