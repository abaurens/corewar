#version 330 core
layout(location = 0) in vec3 pos;

out vec3 uv;

uniform mat4 modelViewMatrix;

void main()
{
	uv = pos;
	//gl_Position = modelViewMatrix * vec4(pos, 1);
	gl_Position = (modelViewMatrix * vec4(pos, 1)).xyww;
}
