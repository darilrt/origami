#version 330 core

uniform sampler2D u_texture;

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    vec4 tex_color = texture2D(u_texture, vec2(
        tex_coord.x,
        1.0f - tex_coord.y
    ));
    frag_color = vec4(tex_color.rgb, 1.0f);
}