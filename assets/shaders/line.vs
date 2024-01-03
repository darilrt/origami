#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec4 vert_color;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec4 color;

void main()
{
    color = vert_color;
    gl_Position = projection * view * model * vec4(vert_position, 1.0);
}
