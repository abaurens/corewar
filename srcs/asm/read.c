/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 06:34:03 by smoreno-          #+#    #+#             */
/*   Updated: 2019/10/19 23:23:31 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/asm.h"
#include <fcntl.h>


int		get_namecom(char *header, char *line, int fd)
{
	int	i;

	i = 0;
	while (*line && *line != '"')
	{
		header[i] = *line;
		line++;
		i++;	
	}
	if (*line == '"')
	{ 
		if (*(line + 1) == '\0')
			return (1);
		else
			return (0);
	}
	if (gnl(fd,&line) > 0)
	{
		header[i] = '\n';
		return (get_namecom(&header[++i], line, fd));
	}
	return (0);
}

int		check_headder(t_header *header, char *line, int fd)
{
	int		i;
	
	if (ft_strlen(line) < 5)
		return (0);
	i = (ft_strncmp(line, NAME_CMD_STRING, 5) == 0) ? 5 : 0;
	i = (i != 5 && ft_strncmp(line, COMMENT_CMD_STRING, 8) == 0) ? 8 : i;
	if (i)
	{
		line += i;
		while (ft_isspace(*line))
			line++;
		if (*line == '"' && i == 5)
		{
			line++;
			if (!get_namecom(header->prog_name, line, fd))
				return (-1);
		}
		else if (*line == '"' && i == 8)
		{
			line++;
			if (!get_namecom(header->comment, line, fd))
				return (-1);	
		}
		if (header->prog_name[0] && header->comment[0])
			return (1);
		return (0);
	}
	return (-1);
}

int		ft_read(t_instruct_head *head, char *path, t_header *header)
{
	int		fd;
	char	*line;
	int		rethd;
	int		ret;
	
	rethd = 0;
	
	if(!(fd = open(path, O_RDONLY)))
		return (0);
	while ((ret = gnl(fd, &line)) > 0)
	{
		if (!*line)
		{
			ft_strdel(&line);
			continue ;
		}
		if (!rethd)
		{	
			if ((rethd = check_headder(header, line, fd)) == -1)
				return (0);
		}
		else
			if (check_instruct(line, head) < 0)
				return (0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (1);
}