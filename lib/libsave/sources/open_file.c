/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:09:48 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/27 18:22:27 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

int			open_file(const char *file, int edit_mode, size_t *filesize)
{
	int			fd;
	struct stat	st;

	if (edit_mode)
		fd = open(file, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	else
		fd = open(file, O_RDONLY);
	if (fd <= 0)
		perror_quit();
	stat(file, &st);
	if (filesize)
		*filesize = st.st_size;
	if (*filesize == 0)
		console_log("FileLoader3030", "creating file...");
	else 
		console_log("FileLoader3030", "opening file...");
	return (fd);
}

void		*dump_file(const char *file, int edit_mode, size_t *size)
{
	const int	fd = open_file(file, edit_mode, size);
	void		*dump;

	if (*size == 0)
		return (NULL);
	if ((dump = (void *)malloc(*size)) == NULL)
		perror_quit();
	if (read(fd, dump, *size) == -1)
		perror_quit();
	close(fd);
	return (dump);
}
