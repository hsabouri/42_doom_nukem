/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:58:43 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/27 18:03:50 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	console_error(const char *service, const char *error)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putstr_fd(service, STDERR_FILENO);
	ft_putstr_fd(C_RESET ": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}

void	console_log(const char *service, const char *log)
{
	ft_putstr_fd(C_CYAN, STDERR_FILENO);
	ft_putstr_fd(service, STDERR_FILENO);
	ft_putstr_fd(C_RESET ": ", STDERR_FILENO);
	ft_putendl_fd(log, STDERR_FILENO);
}

void			perror_quit(void)
{
	perror("System error");
	exit(EXIT_FAILURE);
}
