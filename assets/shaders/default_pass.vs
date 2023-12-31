#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec3 vert_normal;
layout(location = 2) in vec2 vert_tex_coords;

out vec2 tex_coord;

void main()
{
    tex_coord = vert_tex_coords;
    gl_Position = vec4(vert_position * 2.0f, 1.0);
}
