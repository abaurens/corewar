/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:25:33 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/25 14:50:54 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

#include <queue>
#include <glm/glm.hpp>
#include "transform.hpp"
#include "camera.hpp"

class chunk
{
private:
	float		_angle;
	float		_time;
	glm::vec3	_color;
	transform	_transform;

	std::queue<glm::vec3>	_futureColors;

public:
	chunk();
	~chunk();

	void		setColor(glm::vec3 color);
	void		setColor(float r, float g, float b);

	void		changeColor(glm::vec3 color);
	void		changeColor(float r, float g, float b);

	void		update(void);

	void		setPos(vec3 pos);
	void		setRot(vec3 rot);
	void		setScale(vec3 scale);

	void		setPos(float x, float y, float z);
	void		setRot(float x, float y, float z);
	void		setScale(float x, float y, float z);

	glm::vec3	color(void) const { return (_color); }
	glm::vec3	backColor(void) const { return (_futureColors.empty() ? _color : _futureColors.front()); }

	glm::mat4	getTransform(void)
	{
		return (_transform.rotate(radians(_angle),radians(_angle),0.0f).getTransform());
	}
};

#endif