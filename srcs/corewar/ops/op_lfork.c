/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:05:20 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/12 18:07:58 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftmath.h"
#include "ftlib.h"
#include "utils.h"
#include "ftio.h"
#include "vm.h"
#include "op.h"

static void	out(long int pid, t_dir v1, t_dir v2)
{
	write(1, "P     ", ft_max(4 - ft_numlen(pid), 0) + 2);
	ft_putlnbr(pid);
	write(1, " | lfork ", 9);
	ft_putnbr(v1);
	write(1, " (", 2);
	ft_putnbr(v2);
	write(1, ")\n", 2);
}

char		op_lfork(t_vm *vm, t_proc *proc)
{
	t_dir	val;
	t_ind	off;

	off = 1;
	get_dir2(proc, &off, &val);
	if (vm->verbosity & V_OPERATONS)
		out(proc->pid, val, proc->pc + val);
	val %= MEM_SIZE;
	add_process(proc->pc + val, proc);
	move_pc(vm, proc, 3);
	return (proc->carry);
}
