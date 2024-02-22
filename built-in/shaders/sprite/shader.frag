#version 450

layout(location = 0) out vec4 outColor;
layout(location = 1) in vec2 fragUV;

layout(set = 0, binding = 0) uniform Transform {
    mat4 model;
    mat4 view;
    mat4 proj;
};

layout(set = 0, binding = 1) uniform Environment {
    vec3 cameraPosition;
    float time;
};

uniform sampler2D albedo;

void main() {
    vec2 uv = vec2(fragUV.x, fragUV.y);
    vec3 color = texture(albedo, uv).rgb;

    outColor = vec4(color, 1.0);
}