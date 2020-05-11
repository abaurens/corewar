/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 05:34:10 by baurens           #+#    #+#             */
/*   Updated: 2019/11/25 12:45:50 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include <glm/glm.hpp>
# include <glm/gtx/transform.hpp>
# include <glm/gtc/quaternion.hpp>
# include <glm/gtx/quaternion.hpp>

using namespace glm;

class transform
{
private:
	vec3	_pos;
	vec3	_rot;
	vec3	_scale;
	mat4	_mat;

public:
	transform(void);
	transform(vec3 pos, vec3 rot, vec3 scale);

	~transform();

	inline mat4	getTransform(void) const { return (_mat); }

	transform	translate(float x, float y, float z);
	transform	rotate(float x, float y, float z);
	transform	scale(float x, float y, float z);

	void	setPos(vec3 pos);
	void	setRot(vec3 rot);
	void	setScale(vec3 scale);

	void	setPos(float x, float y, float z);
	void	setRot(float x, float y, float z);
	void	setScale(float x, float y, float z);

	friend transform mix(transform a, transform b, float f);
};

#endif