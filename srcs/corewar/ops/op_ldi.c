/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:05:20 by abaurens          #+#    #+#             */
/*   Updated: 2019/12/03 02:25:00 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftmath.h"
#include "output.h"
#include "ftlib.h"
#include "utils.h"
#include "arena.h"
#include "ftio.h"
#include "vm.h"
#include "op.h"

static void	out(t_proc *proc, t_dir v1, t_dir v2, t_dir v3)
{
	corewar_putstr(1, proc->name);
	corewar_write(1, "ldi ", 4);
	corewar_putnbr(1, v1);
	corewar_write(1, " ", 1);
	corewar_putnbr(1, v2);
	corewar_write(1, " r", 2);
	corewar_putnbr(1, v3);
	corewar_write(1, "\n", 1);
	corewar_write(1, "       | -> load from ", 22);
	corewar_putnbr(1, v1);
	corewar_write(1, " + ", 3);
	corewar_putnbr(1, v2);
	corewar_write(1, " = ", 3);
	corewar_putnbr(1, v1 + v2);
	corewar_write(1, " (with pc and mod ", 18);
	corewar_putnbr(1, (proc->pc + ((v1 + v2) % IDX_MOD)) % MEM_SIZE);
	corewar_write(1, ")\n", 2);
}

char		op_ldi(t_vm *vm, t_proc *proc)
{
	t_args	av;
	t_dir	val;
	t_ind	off;

	if (!(off = get_arguments(vm, proc, &av)))
		return (proc->carry);
	av.v1 = apply_type(proc, av.t1, 1, av.v1);
	av.v2 = apply_type(proc, av.t2, 1, av.v2);
	if (vm->verbosity & V_OPERATONS)
		out(proc, av.v1, av.v2, av.v3);
	map_to_var(&val, proc->pc + ((av.v1 + av.v2) % IDX_MOD), sizeof(val));
	proc->regs[av.v3 - 1] = val;
	move_pc(vm, proc, off);
	return (proc->carry);
}
