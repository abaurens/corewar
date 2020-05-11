/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:52:15 by baurens           #+#    #+#             */
/*   Updated: 2019/11/25 13:01:28 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
# define CUBE_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "camera.hpp"

class cube
{
private:

protected:
	float	_vertex[108];
	float	_colors[108];

	GLuint	_vbo;
	GLuint	_vao;
	GLuint	_shader;
	GLuint	_projectionMatrixUniform;
	GLuint	_transformUniform;
	GLuint	_topColUniform;
	GLuint	_botColUniform;

	size_t	vSize, cSize;

public:
	cube();
	~cube();

	void	setTopColor(float r, float g, float b);
	void	setBottomColor(float r, float g, float b);
	void	init(void);
	void	render(camera &cam, glm::mat4 transform) const;
	void	render(camera &cam, glm::mat4 transform, vec3 colTop, vec3 colBot) const;
};

#endif