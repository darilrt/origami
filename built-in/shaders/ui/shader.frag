#version 450

layout(location = 0) out vec4 outColor;
layout(location = 1) in vec2 fragUV;

uniform sampler2D albedo;
uniform sampler2D depth;

void main() {
    vec2 uv = vec2(fragUV.x, 1.0 - fragUV.y);
    vec3 color = texture(albedo, uv).rgb;

    outColor = vec4(color, 1.0);
}