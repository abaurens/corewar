/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 05:37:19 by baurens           #+#    #+#             */
/*   Updated: 2019/11/25 12:45:31 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.hpp"

transform::transform(void) : _pos(0), _rot(0), _scale(1), _mat(1.0) {}

transform::transform(vec3 pos, vec3 rot, vec3 scale) : _pos(pos), _rot(rot), _scale(scale), _mat(glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale)) {}

transform::~transform() {}

transform	transform::translate(float x, float y, float z)
{
	return (transform(_pos + vec3(x, y, z), _rot, _scale));
}

transform	transform::rotate(float x, float y, float z)
{
	return (transform(_pos, _rot + vec3(x, y, z), _scale));
}

transform	transform::scale(float x, float y, float z)
{
	return (transform(_pos, _rot, _scale + vec3(x, y, z)));
}

void	transform::setPos(vec3 pos)
{
	_pos = pos;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

void	transform::setRot(vec3 rot)
{
	_rot = rot;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

void	transform::setScale(vec3 scale)
{
	_scale = scale;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

void	transform::setPos(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

void	transform::setRot(float x, float y, float z)
{
	_rot.x = x;
	_rot.y = y;
	_rot.z = z;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

void	transform::setScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
	_mat = glm::translate(_pos) * toMat4(quat(_rot)) * glm::scale(_scale);
}

transform	mix(transform a, transform b, float f)
{
	return (transform(mix(a._pos, b._pos, f), mix(a._rot, b._rot, f), mix(a._scale, b._scale, f)));
}