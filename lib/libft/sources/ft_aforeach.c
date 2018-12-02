/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aforeach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:47:56 by hugo              #+#    #+#             */
/*   Updated: 2018/12/01 18:09:59 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array		*aforeach(t_array *array, void (*f)(void *elem))
{
	size_t	current;

	if (!array)
		return (NULL);
	current = 0;
	while (current < array->len)
	{
		(*f)(array->first + current * array->elem_size);
		current += 1;
	}
	return (array);
}

t_array		*aforeachi(t_array *array, void (*f)(void *elem, size_t i))
{
	size_t	current;

	if (!array)
		return (NULL);
	current = 0;
	while (current < array->len)
	{
		(*f)(array->first + current * array->elem_size, current);
		current += 1;
	}
	return (array);
}
