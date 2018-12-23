/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:09:48 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/23 18:17:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure_clone.h>

int		open_file(const char *file, int edit_mode, size_t *filesize)
{
	int			fd;
	struct stat	st;

	if (edit_mode)
		fd = open(file, O_CREAT, S_IWUSR | S_IRUSR);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(C_RED "FileLoader3030" C_RESET);
		exit(EXIT_FAILURE);
	}
	stat(file, &st);
	*filesize = st.st_size;
	return (1);
}

void	*dump_file(const char *file, int edit_mode, size_t *size)
{
	const int	fd = open_file(file, edit_mode, size);
	void		*dump;

	if ((dump = (void *)malloc(*size)) == NULL)
	{
		perror(C_RED "FileLoader3030" C_RESET);
		exit(EXIT_FAILURE);
	}
	if (read(fd, dump, *size) == -1)
	{
		perror(C_RED "FileLoader3030" C_RESET);
		exit(EXIT_FAILURE);
	}
	return (dump);
}
