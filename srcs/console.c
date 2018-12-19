/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:58:43 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/14 18:05:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	exit_error(const char *error)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putendl_fd(RESET, STDERR_FILENO);
	exit(EXIT_FAILURE);
}