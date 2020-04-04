#version 330 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 tCoords;
uniform mat4x4 transform;
out vec2 TexCoord0;

void main()
{
    gl_Position = transform*vec4(vPosition,0.0,1.0);
    TexCoord0 = tCoords;    
}