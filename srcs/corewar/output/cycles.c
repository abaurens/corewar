/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:18:52 by abaurens          #+#    #+#             */
/*   Updated: 2020/05/11 16:26:09 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "output.h"
#include "ftlib.h"
#include "ftio.h"
#include "vm.h"

void	out_ctd(t_scycle ctd)
{
	corewar_write(1, "Cycle to die is now ", 20);
	corewar_putlnbr(1, ctd);
	corewar_putchar(1, '\n');
}

void	out_cycles(t_cycle cycle)
{
	corewar_write(1, "It is now cycle ", 16);
	corewar_putunbr(1, cycle);
	corewar_putchar(1, '\n');
}
