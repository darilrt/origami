[[vertex]]
#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec3 vert_normal;
layout(location = 2) in vec2 vert_tex_coords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 normal;
out vec2 tex_coord;

void main()
{
    normal = vert_normal;
    tex_coord = vert_tex_coords;
    gl_Position = projection * view * model * vec4(vert_position, 1.0);
}


[[fragment]]
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
