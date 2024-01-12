#version 330 core

layout (location = 0) out vec4 frag_color;

uniform sampler2D u_albedo;
uniform sampler2D u_normal_ao;
uniform sampler2D u_position_roughness;
uniform sampler2D u_emissive_metallic;

in vec2 tex_coord;

vec3 ligth_dir = normalize(vec3(1.0f, 1.0f, 0.5f));
float ambient = 0.2f;

void main() {
    vec2 uv = vec2(tex_coord.x, 1.0f - tex_coord.y);
    vec4 normal_ao = texture(u_normal_ao, uv);
    vec4 position_roughness = texture(u_position_roughness, uv);
    vec4 emissive_metallic = texture(u_emissive_metallic, uv);
    
    vec4 mx = normal_ao + position_roughness + emissive_metallic;

    vec3 albedo = texture(u_albedo, uv).rgb;
    vec3 normal = normal_ao.rgb;
    float ao = normal_ao.a;
    vec3 position = position_roughness.rgb;
    float roughness = position_roughness.a;
    vec3 emissive = emissive_metallic.rgb;
    float metallic = emissive_metallic.a;

    float diffuse = max(dot(ligth_dir, normalize(normal)), 0.0f);
    float specular = 0.0f;

    float ligth = clamp(ambient + diffuse, 0.0f, 1.0f);
    
    vec3 color = albedo * ligth * ao + vec3(1.0, 1.0, 1.0) * specular;

    frag_color = vec4(color, mx.a);
}