#version 330 core
out vec4 FragColor;

in vec3 uv;

uniform samplerCube cubemap;

void main()
{
	FragColor = texture(cubemap, uv);
}
