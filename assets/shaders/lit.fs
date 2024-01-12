#version 330 core

layout (location = 0) out vec4 albedo_color;
layout (location = 1) out vec4 normal_ao_color;
layout (location = 2) out vec4 position_roughness_color;
layout (location = 3) out vec4 emissive_metallic_color;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_ambient_occlusion;
uniform sampler2D u_roughness;
uniform sampler2D u_emissive;
uniform sampler2D u_metallic;

in vec3 frag_position;
in vec3 frag_normal;
in vec2 tex_coord;

void main() {
    vec3 normal = texture(u_normal, tex_coord).rgb;

    albedo_color = vec4(texture(u_albedo, tex_coord).rgb, 1.0f);
    normal_ao_color = vec4(normal, texture(u_ambient_occlusion, tex_coord).r);
    position_roughness_color = vec4(frag_position, texture(u_roughness, tex_coord).r);
    emissive_metallic_color = vec4(texture(u_emissive, tex_coord).rgb, texture(u_metallic, tex_coord).r);
}