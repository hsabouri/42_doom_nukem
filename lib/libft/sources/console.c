/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:58:43 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/23 18:26:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	exit_error(const char *error)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putendl_fd(C_RESET, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	console_log(const char *service, const char *log)
{
	ft_putstr_fd(C_CYAN, STDERR_FILENO);
	ft_putstr_fd(service, STDERR_FILENO);
	ft_putstr_fd(C_RESET ": ", STDERR_FILENO);
	ft_putendl_fd(log, STDERR_FILENO);
}
