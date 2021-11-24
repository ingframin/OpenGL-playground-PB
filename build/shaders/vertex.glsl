#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoord;

uniform mat4x4 transform;
uniform mat4x4 projection;

out vec3 Color;
out vec2 Texcoord;
void main()
{
    Color = color;
    Texcoord = texcoord;
    gl_Position = transform * projection* vec4(position, 1.0);
    //gl_Position = transform * vec4(position, 1.0);
}