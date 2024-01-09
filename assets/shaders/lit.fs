#version 330 core

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    frag_color = vec4(tex_coord.x, 0.0, tex_coord.y, 1.0f);
}