/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 06:05:50 by smoreno-          #+#    #+#             */
/*   Updated: 2019/12/03 05:06:08 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "endianes.h"
# include "ftlib.h"
# include "ftio.h"
# include "config.h"
# include "op.h"
# include <fcntl.h>
# include <unistd.h>

# define REG_CHAR	 	"0123456789"
# define IS_NAME		1
# define IS_COMMENT		2
# define NAME_DONE		4
# define COMMENT_DONE	8

typedef struct			s_instruc
{
	struct s_instruc	*next;
	struct s_instruc	*prev;
	char				*label;
	t_byte				id;
	uint32_t			plabel;
	uint32_t			byt_index;
	t_arg_type			ocp;
	char				*params_str[3];
	uint32_t			params_bits[3];
	size_t				len;
	int					line_n;
}						t_instruct;

typedef struct			s_instruc_head
{
	t_instruct			*head;
	size_t				length;
	size_t				slen;
	int					line;
	int					cflag;
	int					retrn_parse;
	int					retrn_labels;
	int					av_path;
}						t_instruct_head;

/*
** parsing
*/

int						ft_read(t_instruct_head *head, char *path,
							t_header *header);
int						check_instruct(char *line, t_instruct_head *head);
int						whilegnl(t_instruct_head *head, char **line,
							t_header *header, int fd);
int						check_headder(t_header *header, char *line,
							int fd, int *rethd);
void					ft_fixheader(t_header *header);
int						no_empty_cor(t_instruct_head *head, char *line);
void					set_rethd(int fl, int *rethd);

/*
** free
*/

void					free_split(char **params);
int						instruct_free(t_instruct_head *head);
int						ft_errors(int err, int line_n);

/*
** tools
*/

int						printinst(t_instruct_head *head, int fd);
void					instruct_display(t_instruct *this);
void					instruct_display_all(t_instruct_head *head,
							t_header *header);
int						ft_usage(void);
int						debug_instruct(char *line, t_instruct_head *head);
int						is_paramtype_allowed(char param_type,
							t_instruct *inst, int i);
int						update_progsize(t_instruct_head *head,
							t_instruct *inst);
int						default_op(t_instruct *inst);
int						strtobin(int fd, char *param, uint32_t size);
int						ft_deflab(t_instruct *inst, int *cflag,
							char *line, int len);
int						default_op(t_instruct *inst);
void					default_param(int param_type, t_instruct *inst,
							int i_param);
int						push_label(char **line, t_instruct *inst, int *cflag);
int						push_param(char **line);
int						push_paramtype(char **line, int *len);
int						init_headder(char *line, int *rethd);
int						param_to_inst(char **param_raw, t_instruct *inst,
							char **line);
t_instruct				*add_inst(t_instruct_head *head);
t_instruct				*get_freeinst(t_instruct_head *head);
int						push_str(char *dest, char *src, int len, int start);
void					printheader(int fd, t_header *header);

/*
** get datas
*/

int						ft_getparams(char **line, t_instruct *inst);
int						get_datas(char *s, t_instruct_head *hd,
							t_instruct *inst, size_t i);
int						get_paramlen(int opcode);
char					get_available_type(t_instruct *inst, int param_n);
int						get_octet(t_byte id, char param_type);
t_arg_type				get_ocp(char **param_raw, int param_len,
							t_instruct *inst);

/*
** check strings
*/

int						ft_strcountchar(char *str, char c);
int						is_str_valid(char *str);
int						ft_checkchar(char *str, char *type);
int						is_strn_valid(char *str, int n);

#endif
