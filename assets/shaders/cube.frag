#version 330 core

out vec3 color;

in vec3 fragmentColor;

uniform sampler2D myTextureSampler;

void main()
{
	color = fragmentColor;
}
