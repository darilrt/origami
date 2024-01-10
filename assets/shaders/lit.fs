#version 330 core

uniform sampler2D albedo;

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    vec3 color = texture(albedo, tex_coord).rgb;
    frag_color = vec4(color, 1.0f);
}