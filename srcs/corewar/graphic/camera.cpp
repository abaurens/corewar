/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:47:00 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/25 11:35:37 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <SDL2/SDL.h>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "viewer.hpp"
#include "camera.hpp"
#include "ftmath.h"

camera::camera(void) : _pos(0, 0, -5), _rot(0, 0), _fov(45.0f), _aspect(16.0f / 9.0f), _speed(0.75f), _mouseSpeed(0.005f) {}

camera::camera(vec3 pos, vec2 rot, float fov, float speed, float mouseSpeed) : _pos(pos), _rot(rot), _fov(fov), _speed(speed), _mouseSpeed(mouseSpeed) {}

camera::~camera() {}

vec3	camera::up(void) const
{
	return (glm::cross(right(), forward()));
}

vec3	camera::right(void) const
{
	return (vec3(sin(_rot.y - FT_HPI), 0, cos(_rot.y - FT_HPI)));
}

vec3	camera::forward(void) const
{
	return (vec3(cos(_rot.x) * sin(_rot.y), sin(_rot.x), cos(_rot.x) * cos(_rot.y)));
}

void	camera::update(void)
{
	ivec2	mouse(0, 0);
	vec3	dir(0, 0, 0);
	vec3	front = vec3(sin(_rot.y), 0, cos(_rot.y));

	SDL_GetRelativeMouseState(&mouse.y, &mouse.x);
	if (_anim.size())
	{
		_pos = _anim.front().run();
		if (_anim.front().isOver())
			_anim.pop();
		return ;
	}

	if (keys[KEY_RIGHT]) dir += right();
	if (keys[KEY_LEFT]) dir -= right();
	if (keys[KEY_FRONT]) dir += front;
	if (keys[KEY_BACK]) dir -= front;
	if (keys[KEY_DOWN]) dir.y--;
	if (keys[KEY_UP]) dir.y++;
	if ((dir.x || dir.y || dir.z) != 0.0)
		_pos += (normalize(dir) * _speed);
	if (mouse.x || mouse.y)
	{
		_rot.x -= (float)mouse.x * _mouseSpeed * _speed;
		_rot.y -= (float)mouse.y * _mouseSpeed * _speed;
	}
	if (_rot.x < -FT_HPI)
		_rot.x = -FT_HPI;
	if (_rot.x > FT_HPI)
		_rot.x = FT_HPI;
}

mat4	camera::getMatrix(void)
{
	return (glm::lookAt(_pos, _pos + forward(), up()));
}

mat4	camera::projection(void)
{
	return (glm::perspective(glm::radians(_fov), _aspect, 0.1f, 200.0f));
}

void	camera::moveTo(vec3 target, int time)
{
	if (!_anim.empty())
		_anim.push(animation<vec3>(_anim.back().to(), target, time));
	else
		_anim.push(animation<vec3>(_pos, target, time));
}

void	camera::moveTo(float x, float y, float z, int time)
{
	if (!_anim.empty())
		_anim.push(animation<vec3>(_anim.back().to(), vec3(x, y, z), time));
	else
		_anim.push(animation<vec3>(_pos, vec3(x, y, z), time));
}

void	camera::setRot(vec2 r)
{
	_rot.x = r.x;
	_rot.y = r.y;
}

void	camera::setRot(float x, float y)
{
	_rot.x = x;
	_rot.y = y;
}

void	camera::setPos(vec3 p)
{
	_pos.x = p.x;
	_pos.y = p.y;
	_pos.z = p.z;
}

void	camera::setPos(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
}

void	camera::setAspect(float f)
{
	_aspect = f;
}