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
