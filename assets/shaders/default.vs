#version 330 core

struct Vertex
{
    vec3 position;
    vec3 normal;
    vec2 tex_coords;
};

layout(location = 0) in Vertex vert;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec2 tex_coord;

void main()
{
    tex_coord = vert.tex_coords;
    gl_Position = projection * view * model * vec4(vert.position, 1.0);
}
