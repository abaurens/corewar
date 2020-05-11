/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:45:57 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/22 00:13:39 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_HPP
# define SKYBOX_HPP

#include <GL/glew.h>
#include "camera.hpp"

class skybox
{
private:
	GLuint	_vao;
	GLuint	_vbo;
	GLuint	_shader;
	GLuint	_tex;

	float	_vertex[108];
	size_t	vSize;

public:
	skybox(void);
	~skybox(void);

	void	init(void);
	void	render(camera &cam) const;
};

#endif