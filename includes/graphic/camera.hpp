/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:46:28 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/14 16:40:11 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

using namespace glm;

class	camera
{
private:
	vec3	_pos;
	vec2	_rot;
	float	_fov;

	float _speed;
	float _mouseSpeed;

public:
	camera(void);
	camera(vec3 pos, vec2 rot, float fov, float speed, float mouseSpeed);
	~camera(void);

	vec3	pos(void) const { return (_pos); }
	vec3	up(void) const;
	vec3	right(void) const;
	vec3	forward(void) const;

	void	setRot(vec2 r);
	void	setRot(float x, float y);

	void	setPos(vec3 p);
	void	setPos(float x, float y, float z);

	void	update(void);
	mat4	getMatrix(void);
};

#endif
