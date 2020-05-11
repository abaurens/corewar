/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:00:33 by baurens           #+#    #+#             */
/*   Updated: 2019/11/25 14:48:25 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "cube.hpp"

cube::cube()
{
	/*
		// cube vertex/colors list
		{
			{-0.5, -0.5, -0.5},
			{-0.5, -0.5, +0.5},
			{+0.5, -0.5, +0.5},
			{+0.5, -0.5, -0.5},
			{-0.5, +0.5, -0.5},
			{-0.5, +0.5, +0.5},
			{+0.5, +0.5, +0.5},
			{+0.5, +0.5, -0.5},
		}

		// cube faces list
		{
			front:  {-1, -1, -1}, {-1,  1, -1}, { 1,  1, -1}, { 1, -1, -1} // red
			back:   {-1, -1,  1}, {-1,  1,  1}, { 1,  1,  1}, { 1, -1,  1} // magenta
			top:    {-1,  1, -1}, {-1,  1,  1}, { 1,  1, -1}, { 1,  1,  1} // yellow
			bottom: {-1, -1, -1}, {-1, -1,  1}, { 1, -1, -1}, { 1, -1,  1} // blue
			right:  { 1,  1, -1}, { 1,  1,  1}, { 1, -1, -1}, { 1, -1,  1} // green
			left:   {-1,  1, -1}, {-1,  1,  1}, {-1, -1, -1}, {-1, -1,  1} // cyan
		}
	*/
	const float	v[108] = {
		// top
		0.5f, 0.5f, -0.5f,		-0.5f, 0.5f, 0.5f,		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,		-0.5f, 0.5f, -0.5f,		-0.5f, 0.5f, 0.5f,

		// bottom
		0.5f, -0.5f, 0.5f,		-0.5f, -0.5f, -0.5f,	0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,		-0.5f, -0.5f, 0.5f,		-0.5f, -0.5f, -0.5f,

		// back
		0.5f, -0.5f, -0.5f,		-0.5f, 0.5f, -0.5f,		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,		-0.5f, -0.5f, -0.5f,	-0.5f, 0.5f, -0.5f,

		// right
		-0.5f, -0.5f, -0.5f,	-0.5f, 0.5f, 0.5f,		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,	-0.5f, -0.5f, 0.5f,		-0.5f, 0.5f, 0.5f,

		// face
		-0.5f, -0.5f, 0.5f,		0.5f, 0.5f, 0.5f,		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,		0.5f, -0.5f, 0.5f,		0.5f, 0.5f, 0.5f,

		// left
		0.5f, -0.5f, 0.5f,		0.5f, 0.5f, -0.5f,		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,		0.5f, -0.5f, -0.5f,		0.5f, 0.5f, -0.5f,
	};

	const float	c[108] = {
		1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,

		1.0f, 0.5f, 1.0f,		1.0f, 0.5f, 1.0f,		1.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,		1.0f, 0.5f, 1.0f,		1.0f, 0.5f, 1.0f,

		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
		
		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,

		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,

		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,		0.0f, 0.53f, 0.8f,
	};

	for (int i = 0; i < 108; ++i)
	{
		_vertex[i] = v[i];
		_colors[i] = c[i];
	}

	vSize = sizeof(float) * 108;
	cSize = sizeof(float) * 108;
}

void	cube::setTopColor(float r, float g, float b)
{
	float	newColor[3*6] = {
		r, g, b,	r, g, b,	r, g, b,
		r, g, b,	r, g, b,	r, g, b,
	};

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, vSize, sizeof(newColor), newColor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	cube::setBottomColor(float r, float g, float b)
{
	float	newColor[3*6] = {
		r, g, b,	r, g, b,	r, g, b,
		r, g, b,	r, g, b,	r, g, b,
	};

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, vSize + sizeof(newColor), sizeof(newColor), newColor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

cube::~cube()
{
	if (glIsVertexArray(_vao))
		glDeleteVertexArrays(1, &_vao);
	if (glIsBuffer(_vbo))
		glDeleteBuffers(1, &_vbo);
	if (glIsShader(_shader))
		glDeleteShader(_shader);
}

void	cube::init(void)
{
	if (glIsVertexArray(_vao))
		glDeleteVertexArrays(1, &_vao);
	if (glIsBuffer(_vbo))
		glDeleteBuffers(1, &_vbo);
	if (glIsShader(_shader))
		glDeleteShader(_shader);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vSize + cSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, _vertex);
	glBufferSubData(GL_ARRAY_BUFFER, vSize, cSize, _colors);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_shader = loadShaders("assets/shaders/cube.vert", "assets/shaders/cube.frag");
	_projectionMatrixUniform = glGetUniformLocation(_shader, "projectionMatrix");
	_transformUniform = glGetUniformLocation(_shader, "transform");
	_topColUniform = glGetUniformLocation(_shader, "topCol");
	_botColUniform = glGetUniformLocation(_shader, "botCol");

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)vSize);
			glEnableVertexAttribArray(1);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void	cube::render(camera &cam, glm::mat4 transform) const
{
	glm::mat4	proj = cam.projection() * cam.getMatrix() * transform;

	glUseProgram(_shader);
	glBindVertexArray(_vao);
	glUniformMatrix4fv(_projectionMatrixUniform, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(_transformUniform, 1, GL_FALSE, &transform[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3*12);
	glBindVertexArray(0);
	glUseProgram(0);
}

void	cube::render(camera &cam, glm::mat4 transform, vec3 colTop, vec3 colBot) const
{
	glm::mat4 proj = cam.projection() * cam.getMatrix();

	glUseProgram(_shader);
	glBindVertexArray(_vao);
	glUniformMatrix4fv(_projectionMatrixUniform, 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(_transformUniform, 1, GL_FALSE, &transform[0][0]);
	glUniform3fv(_topColUniform, 1, &colTop.x);
	glUniform3fv(_botColUniform, 1, &colBot.x);
	glDrawArrays(GL_TRIANGLES, 0, 3*12);
	glBindVertexArray(0);
	glUseProgram(0);
}
