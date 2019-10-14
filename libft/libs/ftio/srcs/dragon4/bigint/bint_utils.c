/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 02:27:54 by abaurens          #+#    #+#             */
/*   Updated: 2019/01/28 20:55:03 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

void		swap(uintptr_t *n1, uintptr_t *n2)
{
	*n2 ^= (*n1 ^= *n2);
	*n1 ^= *n2;
}
