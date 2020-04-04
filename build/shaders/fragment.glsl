#version 150 core

out vec4 outColor;
uniform vec3 in_color;
void main()
{
    outColor = vec4(in_color,1.0);
}