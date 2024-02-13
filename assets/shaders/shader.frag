#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragUV;

layout(std140, binding = 0) uniform Transform {
    mat4 model;
    mat4 view;
    mat4 proj;
};

layout(std140, binding = 1) uniform Environment {
    vec3 camera;
    float time;
};

uniform sampler2D albedo;

vec3 light_dir = normalize(vec3(1.0, 1.0, 1.0));

void main() {
    vec4 tn = normalize(model * vec4(fragNormal, 1.0));
    float NdotL = max(dot(tn.xyz, light_dir), 0.0);
    float light = 0.1 + 0.9 * NdotL;

    vec3 color = texture(albedo, fragUV).rgb * light ;
    outColor = vec4(color, 1.0);
}