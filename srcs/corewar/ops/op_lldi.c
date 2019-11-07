/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:05:20 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/07 21:05:33 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "arena.h"
#include "ftio.h"
#include "vm.h"
#include "op.h"

char	op_lldi(t_vm *vm, t_proc *proc)
{
	t_args	av;
	t_dir	val;
	t_ind	off;

	if (!(off = get_arguments(vm, proc, &av)))
		return (proc->carry);
	av.v1 = apply_type(proc, av.t1, 1, av.v1);
	av.v2 = apply_type(proc, av.t2, 1, av.v2);
	if (vm->verbosity & V_OPERATONS)
	{
		ft_printf("P %4d | lldi %d %d r%d\n", proc->pid, av.v1, av.v2, av.v3);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			av.v1, av.v2, (av.v1 + av.v2), proc->pc + av.v1 + av.v2);
	}
	map_to_var(&val, proc->pc + av.v1 + av.v2, sizeof(val));
	proc->regs[av.v3 - 1] = val;
	move_pc(vm, proc, off);
	return (proc->carry);
}
