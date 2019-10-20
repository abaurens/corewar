/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 06:05:50 by smoreno-          #+#    #+#             */
/*   Updated: 2019/10/20 07:25:04 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <stdlib.h>
#include "op.h"
//#include "ftlib.h"
#include "../../libft/includes/ftlib.h"
#include "../../libft/includes/ftio.h"

typedef struct 	s_instruc
{
	struct s_instruc 	*next;
	struct s_instruc 	*prev;
	char				*label;
	char				id;
	uint32_t			plabel;
	t_arg_type			ocp;
	uint32_t			parms[3];
	size_t				len;
} 				t_instruct;

typedef struct 	s_instruc_head
{
	t_instruct	*head;
	size_t		length;
	size_t		slen;
} 				t_instruct_head;

/*
** parsing
*/

int		ft_read(t_instruct_head *head, char *path, t_header *header);
int		check_instruct(char *line, t_instruct_head *head);

/*
** free
*/

void	instruct_free(t_instruct_head *head);

/*
** tools
*/

void	ft_bprint_fd(void *ptr, int nbits, int fd);
void	ft_bprint_fd_rev(void *ptr, int nbits, int fd);
void	instruct_display(t_instruct *this);
void	instruct_display_all(t_instruct_head *head);

#endif