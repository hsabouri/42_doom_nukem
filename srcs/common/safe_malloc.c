/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:35:21 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/27 11:35:22 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*safe_malloc(size_t size, char *location)
{
	void *ret;

	if (!(ret = malloc(size)))
	{
		console_error(location, "Could not allocate memory");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

t_array	safe_anew(void *first, size_t len, size_t elem_size, char *location)
{
	t_array ret;

	ret = anew(first, len, elem_size);
	if (ret.allocated == 0 && len == 0 && elem_size == 0)
	{
		console_error(location, "Could not allocate memory");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
