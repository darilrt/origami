#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragNormal;

layout(binding = 0) uniform bindings 
{
    float time;
    float c;
};

void main() {
    // color *= vec3(0.5 + 0.5 * sin(time), 0.5 + 0.5 * cos(time), 0.5 + 0.5 * sin(time + 1.0));
    
    outColor = vec4(c, c, c, 1.0);
}