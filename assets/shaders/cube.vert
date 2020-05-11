#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;

uniform vec3 topCol = vec3(1, 1, 1);
uniform vec3 botCol = vec3(0, 1, 1);
uniform mat4 projectionMatrix;
uniform mat4 transform;

out vec3 fragmentColor;

void main()
{
	gl_Position = projectionMatrix * transform * vec4(pos, 1);
	if (col == vec3(1, 0, 1))
		fragmentColor = topCol;
	else if (col == vec3(1, 0.5, 1))
		fragmentColor = botCol;
	else
		fragmentColor = col;
}
