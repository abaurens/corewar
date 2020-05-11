/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:35:31 by abaurens          #+#    #+#             */
/*   Updated: 2020/05/11 16:28:59 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "output.h"
#include "ftlib.h"
#include "vm.h"

static const int		g_ten_pow[] = {
	1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1, 0
};

static const long int	g_lten_pow[] = {
	1000000000000000000, 100000000000000000, 10000000000000000,
	1000000000000000, 100000000000000, 10000000000000, 1000000000000,
	100000000000, 10000000000, 1000000000, 100000000, 10000000, 1000000,
	100000, 10000, 1000, 100, 10, 1, 0
};

void					corewar_putlunbr(const int fd,
							register unsigned long int n)
{
	register int	i;

	i = 0;
	g_buff[g_pos] = '0';
	if (n == 0)
		++g_pos;
	while (g_ten_pow[i] && !(n / g_ten_pow[i]))
		++i;
	while (g_ten_pow[i])
	{
		if (g_pos >= OUT_BUF_SIZE)
			flush_buffer(fd);
		g_buff[g_pos++] = ((n / g_ten_pow[i])) + '0';
		n %= g_ten_pow[i++];
	}
	if (g_pos >= OUT_BUF_SIZE)
		flush_buffer(fd);
}

void					corewar_putlnbr(const int fd, register long int n)
{
	register int	i;

	i = 0;
	g_buff[g_pos] = '0';
	if (n == 0)
		++g_pos;
	if (n < 0)
		g_buff[g_pos++] = '-';
	while (g_lten_pow[i] && !(n / g_lten_pow[i]))
		++i;
	while (g_lten_pow[i])
	{
		if (g_pos >= OUT_BUF_SIZE)
			flush_buffer(fd);
		if ((g_buff[g_pos] = ((n / g_lten_pow[i]))) < 0)
			g_buff[g_pos] *= -1;
		g_buff[g_pos++] += '0';
		n %= g_lten_pow[i++];
	}
	if (g_pos >= OUT_BUF_SIZE)
		flush_buffer(fd);
}

void					corewar_putunbr(const int fd, register unsigned int n)
{
	register int	i;

	i = 0;
	g_buff[g_pos] = '0';
	if (n == 0)
		++g_pos;
	while (g_ten_pow[i] && !(n / g_ten_pow[i]))
		++i;
	while (g_ten_pow[i])
	{
		if (g_pos >= OUT_BUF_SIZE)
			flush_buffer(fd);
		g_buff[g_pos++] = ((n / g_ten_pow[i])) + '0';
		n %= g_ten_pow[i++];
	}
	if (g_pos >= OUT_BUF_SIZE)
		flush_buffer(fd);
}

void					corewar_putnbr(const int fd, register int n)
{
	register int	i;

	i = 0;
	g_buff[g_pos] = '0';
	if (n == 0)
		++g_pos;
	if (n < 0)
		g_buff[g_pos++] = '-';
	while (g_ten_pow[i] && !(n / g_ten_pow[i]))
		++i;
	while (g_ten_pow[i])
	{
		if (g_pos >= OUT_BUF_SIZE)
			flush_buffer(fd);
		if ((g_buff[g_pos] = ((n / g_ten_pow[i]))) < 0)
			g_buff[g_pos] *= -1;
		g_buff[g_pos++] += '0';
		n %= g_ten_pow[i++];
	}
	if (g_pos >= OUT_BUF_SIZE)
		flush_buffer(fd);
}
