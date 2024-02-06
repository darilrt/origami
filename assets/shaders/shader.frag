#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragNormal;

layout(binding = 0) uniform bindings 
{
    float time;
};

void main() {
    outColor = vec4(fragNormal, 1.0);
}