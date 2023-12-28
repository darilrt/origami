#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

out vec3 v_color;

void main()
{
    v_color = color;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
