/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:34:23 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/22 05:33:40 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glm/gtx/transform.hpp>
#include "texture.hpp"
#include "shader.hpp"
#include "skybox.hpp"

skybox::skybox(void)
{
	/*const float	v[108] = {
		 0.5f,  0.5f, -0.5f,	-0.5f, -0.5f, -0.5f,	-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,	 0.5f, -0.5f, -0.5f,	-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, -0.5f,	-0.5f,  0.5f,  0.5f,	-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,	-0.5f, -0.5f,  0.5f,	-0.5f,  0.5f,  0.5f,

		 0.5f, -0.5f,  0.5f,	-0.5f, -0.5f, -0.5f,	 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,	-0.5f, -0.5f,  0.5f,	-0.5f, -0.5f, -0.5f,

		 0.5f,  0.5f,  0.5f,	 0.5f, -0.5f, -0.5f,	 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,	 0.5f,  0.5f,  0.5f,	 0.5f, -0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,	-0.5f,  0.5f, -0.5f,	-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,	 0.5f,  0.5f, -0.5f,	-0.5f,  0.5f, -0.5f,

		 0.5f,  0.5f,  0.5f,	-0.5f,  0.5f,  0.5f,	 0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,	-0.5f, -0.5f,  0.5f,	 0.5f, -0.5f,  0.5f,
	};*/
	float v[] = {
		-1.0f, 1.0f, -1.0f,		-1.0f, -1.0f, -1.0f,	1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 1.0f, -1.0f,		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,		-1.0f, -1.0f, -1.0f,	-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,		-1.0f, 1.0f, 1.0f,		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,		1.0f, -1.0f, 1.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, -1.0f,		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, -1.0f, 1.0f,		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,		1.0f, 1.0f, -1.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		-1.0f, 1.0f, 1.0f,		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,	-1.0f, -1.0f, 1.0f,		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		-1.0f, -1.0f, 1.0f,		1.0f, -1.0f, 1.0f
};

	for (int i = 0; i < 108; ++i)
	{
		_vertex[i] = v[i];
	}

	vSize = sizeof(v);
}

skybox::~skybox(void)
{
	if (glIsVertexArray(_vao))
		glDeleteVertexArrays(1, &_vao);
	if (glIsBuffer(_vbo))
		glDeleteBuffers(1, &_vbo);
	if (glIsShader(_shader))
		glDeleteShader(_shader);
	if (glIsTexture(_tex))
		glDeleteTextures(1, &_tex);
}

void	skybox::init(void)
{
	if (glIsVertexArray(_vao))
		glDeleteVertexArrays(1, &_vao);
	if (glIsBuffer(_vbo))
		glDeleteBuffers(1, &_vbo);
	if (glIsShader(_shader))
		glDeleteShader(_shader);
	if (glIsTexture(_tex))
		glDeleteTextures(1, &_tex);

	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, _vertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_shader = loadShaders("assets/shaders/skybox.vert", "assets/shaders/skybox.frag");
	_tex = loadCubemap(std::vector<std::string>({
		"assets/textures/right.tga",
		"assets/textures/left.tga",
		"assets/textures/top.tga",
		"assets/textures/bottom.tga",
		"assets/textures/front.tga",
		"assets/textures/back.tga",
	}));

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void	skybox::render(camera &cam) const
{
	glm::mat4 mvp = cam.projection() * glm::mat4(glm::mat3(cam.getMatrix()));

	glDepthFunc(GL_LEQUAL);
		glUseProgram(_shader);
		glUniformMatrix4fv(glGetUniformLocation(_shader, "modelViewMatrix"), 1, GL_FALSE, &mvp[0][0]);
			glBindVertexArray(_vao);
				glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);
					glDrawArrays(GL_TRIANGLES, 0, 3*12);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glBindVertexArray(0);
		glUseProgram(0);
	glDepthFunc(GL_LESS);
}