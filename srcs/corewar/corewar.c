/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:24:26 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/12 14:53:33 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "ftlib.h"
#include "ftio.h"
#include "vm.h"

t_byte		g_map[MEM_SIZE];
t_lst		g_procs;

static int	print_help(char const *const n)
{
	ft_printf("Usage: %s [[-d | -dump] N -v N -a] <champion1.cor> <...>\n", n);
	ft_printf(UOP, "-a", "", "Prints output from \"aff\""USGAFF);
	ft_printf(UOP, "-dump", " N", "Dumps memory after N cycles then exits");
	ft_printf(UOP, "-d", " N", "Dumps memory after N cycles then exits (zaz)");
	ft_printf(UOP, "-v", " N", "Verbosity levels, "\
									"can be added together to enable several");
	ft_printf(UVB, "- 0", "Show only essentials (default)");
	ft_printf(UVB, "- 1", "Show lives");
	ft_printf(UVB, "- 2", "Show cycles");
	ft_printf(UVB, "- 4", "Show operations (Params are NOT litteral ...)");
	ft_printf(UVB, "- 8", "Show deaths");
	ft_printf(UVB, "- 16", "Show PC movements (Except for jumps)");
	return (0);
}

t_champ		*get_player(t_vm *vm, uint32_t pid)
{
	uint32_t	i;
	t_champ		*p;

	i = 0;
	p = vm->players;
	while (i++ < vm->psize)
	{
		if (p->pid == pid)
			return (p);
		p++;
	}
	return (NULL);
}

void		destruct(void)
{
	clear_procs();
}

int			main(int ac __attribute__((unused)), char **av)
{
	size_t	i;
	t_vm	vm;

	i = 0;
	if (ac == 1)
		return (print_help(*av));
	ft_bzero(&g_procs, sizeof(t_lst));
	parse_args(&vm, av + 1);
	ft_putstr("Introducing contestants...\n");
	while (i < vm.psize)
	{
		ft_printf("* Player %u, weighing %lu bytes, \"%s\" (\"%s\") !\n",
				vm.players[i].pid, vm.players[i].size,
				vm.players[i].name, vm.players[i].comm);
		++i;
	}
	vm_loop(&vm);
	ft_printf(WINMSG, vm.winer->pid, vm.winer->name);
	return (0);
}
