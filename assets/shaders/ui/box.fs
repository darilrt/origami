#version 330 core

layout (location = 0) out vec4 albedo_color;
layout (location = 1) out vec4 normal_ao_color;
layout (location = 2) out vec4 position_roughness_color;
layout (location = 3) out vec4 emissive_metallic_color;

uniform vec4 color;

in vec3 frag_position;
in vec3 frag_normal;
in vec2 tex_coord;

void main() {
    albedo_color = color;
    normal_ao_color = vec4(1.0, 1.0, 1.0, 1.0);
    position_roughness_color = vec4(frag_position, 1.0);
    emissive_metallic_color = vec4(0.0, 0.0, 0.0, 1.0);
}