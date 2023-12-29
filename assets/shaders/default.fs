#version 330 core

uniform sampler2D tex;

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    vec4 tex_color = texture2D(tex, tex_coord);

    if (tex_color.a < 0.1f)
        discard;

    frag_color = vec4(tex_color.rgb, 1.0f);
}