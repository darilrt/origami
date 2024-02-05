#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec3 fragNormal;

layout(binding = 0) uniform UniformBufferObject {
    float time;
    vec3 color;
};

void main() {
    fragNormal = normal;

    vec3 position2 = vec3(position.x, position.y, position.z) * (1.0 + 0.1 * sin(time));
    
    gl_Position = vec4(position2, 1.0);
}