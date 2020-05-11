/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 07:24:08 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/08 07:30:55 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** ici on regarde le premier char pour savoir si rX ou si % ou si rien
*/

int			ft_checkcharn(char *str, char *type, int n)
{
	int		j;

	j = 0;
	while (str[j] && j < n)
	{
		if (ft_contains(str[j], type) != 1 && !ft_isspace(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int			ft_checkchar(char *str, char *type)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (ft_contains(str[j], type) != 1 && !ft_isspace(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int			is_strn_valid(char *str, int n)
{
	if (!*str)
		return (0);
	if (*str == LABEL_CHAR)
	{
		str++;
		return (ft_checkcharn(str, LABEL_CHARS, n));
	}
	else
	{
		if (*str == '-')
			str++;
		return (ft_checkcharn(str, REG_CHAR, n));
	}
	return (0);
}

/*
** return le nombre d'occurence d'un char dans une *str
** est utilise pour compter le nombre de ',' qui separent les parametres
*/

int			ft_strcountchar(char *str, char c)
{
	int		sum;

	sum = 0;
	while (*str)
	{
		if (*str == c)
			sum += 1;
		str += 1;
	}
	return (sum);
}

int			is_str_valid(char *str)
{
	if (!*str)
		return (0);
	if (*str == LABEL_CHAR)
	{
		str++;
		return (ft_checkchar(str, LABEL_CHARS));
	}
	else
	{
		if (*str == '-')
			str++;
		return (ft_checkchar(str, REG_CHAR));
	}
	return (0);
}
