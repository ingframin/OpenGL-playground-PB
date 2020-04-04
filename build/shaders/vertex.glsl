#version 430 core

layout(location = 0) in vec4 vPosition;
uniform mat4x4 transform;

void main()
{
    gl_Position = transform*vPosition;
}