/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 08:15:32 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/25 11:34:02 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_HPP
# define ANIMATION_HPP

#include <glm/glm.hpp>

template <typename T>
class animation
{
private:
	float	_step;
	float	_time;
	float	_duration;

	T		_from;
	T		_to;
public:
	animation(void);
	animation(T from, T to, float duration);
	~animation();

	T	now(void);
	T	run(void);

	bool	isOver(void) const { return (_time >= _duration); }
	T		to() const { return (_to); }
	T		from() const { return (_from); }
};


#endif