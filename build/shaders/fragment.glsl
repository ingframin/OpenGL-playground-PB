#version 330 core
in vec2 Texcoord;
out vec4 outColor;
uniform vec3 in_color;
uniform sampler2D tex;

void main()
{
    outColor = texture(tex, Texcoord) *vec4(in_color,1.0);
}