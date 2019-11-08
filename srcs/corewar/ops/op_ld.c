/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:05:20 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/08 20:20:51 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_DISABLE_WARNINGS

#include "utils.h"
#include "ftio.h"
#include "vm.h"
#include "op.h"

char	op_ld(t_vm *vm, t_proc *proc)
{
	t_args	av;
	t_ind	off;

	if (!(off = get_arguments(vm, proc, &av)))
	{
		av.v1 = apply_type(proc, av.t1, 1, av.v1);
		if (proc->pid == 4)
			ft_dprintf(2, "cycle = %4d | ld (%02b)%d\n", vm->cycles, av.t1, av.v1);
		return (proc->carry);
	}
	av.v1 = apply_type(proc, av.t1, 1, av.v1);
	if (vm->verbosity & V_OPERATONS)
		ft_printf("P %4d | ld %d r%d\n", proc->pid, av.v1, av.v2);
	move_pc(vm, proc, off);
	return (!(proc->regs[av.v2 - 1] = av.v1));
}
