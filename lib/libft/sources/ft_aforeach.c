/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aforeach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:47:56 by hugo              #+#    #+#             */
/*   Updated: 2018/12/21 12:55:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array		*aforeach(t_array *array, void (*f)(void *))
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

t_array		*aforeachi(t_array *array, void (*f)(void *, size_t))
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

t_array		*aforeach_state(t_array *array, void (*f)(void *, void *),
void *state)
{
	size_t	current;

	if (!array)
		return (NULL);
	current = 0;
	while (current < array->len)
	{
		(*f)(array->first + current * array->elem_size, state);
		current += 1;
	}
	return (array);
}
