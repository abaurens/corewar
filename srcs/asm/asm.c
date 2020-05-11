/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 05:19:53 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/10 06:33:58 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		creat_file(t_instruct_head *head, char *av, t_header *header)
{
	char	*name;
	char	*npos;
	int		fd;

	if ((npos = ft_strrchr(av, '.')) != NULL)
	{
		if (!(name = ft_strnew(npos - av + 4)))
			return (-9);
		name = ft_strncpy(name, av, npos - av);
	}
	else
	{
		npos = av + ft_strlen(av);
		if (!(name = ft_strnew(ft_strlen(av) + 4)))
			return (-9);
	}
	ft_strlcat(name, ".cor", npos - av + 5);
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600)) < 0)
		return (-9);
	printheader(fd, header);
	printinst(head, fd);
	ft_printf("%s written\n", name);
	ft_strdel(&name);
	return (close(fd));
}

int		check_labels(t_instruct_head *head, t_instruct *tmp, t_instruct *kev,
	int k)
{
	int			val;
	size_t		v;

	v = -1;
	while (++v < head->slen)
	{
		if (kev->label && ft_strcmp(kev->label, &(tmp->params_str[k][1])) == 0)
		{
			val = kev->byt_index - tmp->byt_index;
			ft_strdel(&(tmp->params_str[k]));
			tmp->params_str[k] = ft_itoa(val);
			break ;
		}
		kev = kev->next;
	}
	if (v == head->slen)
	{
		head->line = tmp->line_n;
		if (head->cflag)
			tmp->params_str[k][0] = 0;
		else
			return (-1);
	}
	return (0);
}

int		set_labels(t_instruct_head *head)
{
	t_instruct	*tmp;
	t_instruct	*kev;
	size_t		i;
	int			k;

	tmp = head->head;
	i = 0;
	while (i < head->slen)
	{
		k = 0;
		while (k < 3 && tmp->params_str[k])
		{
			if (tmp->params_str[k][0] == LABEL_CHAR)
			{
				kev = head->head;
				if (check_labels(head, tmp, kev, k) == -1)
					return (-1);
			}
			k++;
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int		ft_init(t_instruct_head *head, t_header *header, char **av)
{
	if (!head->length)
		return (ft_errors(-6, 0));
	header->prog_size = head->length;
	head->retrn_labels = set_labels(head);
	if (head->retrn_labels < 0)
		ft_errors(head->retrn_labels, head->line);
	if (head->retrn_labels && av[1][0] == '-' && ft_contains('a', av[1]))
	{
		instruct_display_all(head, header);
		return (0);
	}
	if (head->retrn_labels > 0 && head->retrn_parse > 0)
		if (creat_file(head, av[head->av_path], header))
			return (ft_errors(9, 0));
	return (1);
}

int		main(int ac, char **av)
{
	t_instruct_head head;
	t_header		header;

	ft_bzero(&head, sizeof(t_instruct_head));
	head.av_path = ac - 1;
	if (ac == 1)
		return (ft_usage());
	if (av[1][0] == '-')
	{
		if (ft_contains('c', av[1]))
			head.cflag = 1;
		if (ac < 3)
			return (ft_printf("Error\n"));
	}
	ft_bzero(&header, sizeof(t_header));
	header.magic = COREWAR_EXEC_MAGIC;
	head.retrn_parse = ft_read(&head, av[head.av_path], &header);
	if (head.retrn_parse == 1)
	{
		if (ft_init(&head, &header, av) == 0)
			return (instruct_free(&head));
	}
	else
		ft_errors(head.retrn_parse, head.line);
	return (instruct_free(&head));
}
