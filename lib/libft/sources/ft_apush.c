/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:30:23 by hugo              #+#    #+#             */
/*   Updated: 2018/12/02 19:18:25 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_array	*push_end(t_array *array, void *element)
{
	ft_memmove(array->first + array->len * array->elem_size,
		element, array->elem_size);
	array->len += 1;
	return (array);
}

static t_array	*shift_and_push(t_array *array, void *element)
{
	ft_memmove(array->first - array->elem_size, array->first,\
		array->len * array->elem_size);
	array->first -= array->elem_size;
	return (push_end(array, element));
}

static t_array	*grow_end(t_array *array, void *element)
{
	void *new_mem;

	new_mem = (void *)malloc((array->len + 1) * array->elem_size);
	ft_memmove(new_mem, array->first, array->len * array->elem_size);
	free(array->mem);
	array->mem = new_mem;
	array->first = new_mem;
	array->allocated = (array->len + 1) * array->elem_size;
	return (push_end(array, element));
}

t_array			*apush(t_array *array, void *element)
{
	size_t	before;
	size_t	after;

	if (!element || array == NULL)
		return (array);
	before = array->first - array->mem;
	after = array->allocated - before - array->len * array->elem_size;
	if (after >= array->elem_size)
		return (push_end(array, element));
	else if (before >= array->elem_size)
		return (shift_and_push(array, element));
	else
		return (grow_end(array, element));
}
