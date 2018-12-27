/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:09:48 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/26 19:03:53 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

static void	perror_quit(void)
{
	perror(C_RED "FileLoader3030" C_RESET);
	exit(EXIT_FAILURE);
}

int			open_file(const char *file, int edit_mode, size_t *filesize)
{
	int			fd;
	struct stat	st;

	if (edit_mode)
	{
		fd = open(file, O_CREAT, S_IWUSR | S_IRUSR);
		console_log("UniverseSaver3030", "creating file...");
	}
	else
	{
		fd = open(file, O_RDONLY);
		console_log("UniverseSaver3030", "opening file...");
	}
	if (fd == -1)
		perror_quit();
	stat(file, &st);
	if (filesize)
		*filesize = st.st_size;
	return (fd);
}

void		*dump_file(const char *file, int edit_mode, size_t *size)
{
	const int	fd = open_file(file, edit_mode, size);
	void		*dump;

	if ((dump = (void *)malloc(*size)) == NULL)
		perror_quit();
	if (read(fd, dump, *size) == -1)
		perror_quit();
	close(fd);
	return (dump);
}
