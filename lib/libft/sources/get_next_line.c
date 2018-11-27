/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:47:51 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/30 13:56:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	reload(const int fd, t_file *fl)
{
	int	rreturn;

	if (fl == NULL)
	{
		fl = (t_file *)malloc(sizeof(t_file));
		fl->rl = BUFF_SIZE;
		fl->ps = fl->rl;
	}
	bzero(fl->bf, BUFF_SIZE);
	rreturn = read(fd, fl->bf, BUFF_SIZE);
	fl->bf[BUFF_SIZE] = '\0';
	fl->ps = 0;
	fl->rl = rreturn;
	return (rreturn);
}

static void	to_endl(char **line, int *ln, t_file *fl, char *ptr)
{
	char *tmp;

	tmp = *line;
	*line = ft_memjoin(*line, fl->bf + fl->ps, *ln, ptr - (fl->bf + fl->ps));
	*ln += ptr - (fl->bf + fl->ps);
	free(tmp);
	fl->ps += ptr - (fl->bf + fl->ps) + 1;
}

int			get_next_line(const int fd, char **line)
{
	static t_file	fl = {0, 0, {0}};
	char			*tmp;
	char			*ptr;
	int				ln;

	if (fl.ps >= fl.rl)
		if (reload(fd, &fl) == -1)
			return (-1);
	if (!(*line = ft_strnew(1)))
		return (-1);
	ln = 0;
	while (!ft_memchr(fl.bf + fl.ps, '\n', fl.rl - fl.ps) && fl.rl != 0)
	{
		tmp = *line;
		*line = ft_memjoin(*line, fl.bf + fl.ps, ln, fl.rl - fl.ps);
		ln += (fl.rl - fl.ps);
		if (reload(fd, &fl) == -1)
			return (-1);
		free(tmp);
	}
	if ((ptr = ft_memchr(fl.bf + fl.ps, '\n', fl.rl - fl.ps)))
		to_endl(line, &ln, &fl, ptr);
	if (ln == 0)
		*line = ft_strnew(1);
	return ((ln == 0 && fl.rl == 0) ? 0 : 1);
}
