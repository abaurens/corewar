/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 08:15:48 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/25 11:37:03 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.hpp"
#include "transform.hpp"
#include "viewer.hpp"

template <typename T>
animation<T>::animation(void) : _step(1.0f / TPS), _time(0.0f), _duration(0.0f), _from(), _to() {}

template <typename T>
animation<T>::animation(T from, T to, float duration) : _step(1.0f / TPS), _time(0.0f), _duration(duration), _from(from), _to(to) {}

template <typename T>
animation<T>::~animation() {}

template <typename T>
T	animation<T>::now(void)
{
	return (mix(_from, _to, _time / _duration));
}

template <typename T>
T	animation<T>::run(void)
{
	_time += _step;
	return (now());
}

template class animation<glm::vec2>;
template class animation<glm::vec3>;
template class animation<transform>;