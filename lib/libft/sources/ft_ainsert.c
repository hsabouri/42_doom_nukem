/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ainsert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:09:54 by hugo              #+#    #+#             */
/*   Updated: 2018/12/02 19:18:33 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_array	*insert_start(t_array *array, void *element)
{
	ft_memmove(array->first - array->elem_size, element, array->elem_size);
	array->first -= array->elem_size;
	array->len += 1;
	return (array);
}

static t_array	*shift_and_insert(t_array *array, void *element)
{
	ft_memmove(array->first + array->elem_size,
		array->first, array->len * array->elem_size);
	array->first += array->elem_size;
	return (insert_start(array, element));
}

static t_array	*grow_start(t_array *array, void *element)
{
	void *new_mem;

	new_mem = (void *)malloc((array->len + 1) * array->elem_size);
	ft_memmove(new_mem + array->elem_size,
		array->first, array->len * array->elem_size);
	array->mem = new_mem;
	array->first = new_mem + array->elem_size;
	array->allocated = (array->len + 1) * array->elem_size;
	return (insert_start(array, element));
}

t_array			*ainsert(t_array *array, void *element)
{
	size_t	before;
	size_t	after;

	if (!element || array == NULL)
		return (array);
	before = array->first - array->mem;
	after = array->allocated - before - array->len * array->elem_size;
	if (before >= array->elem_size)
		return (insert_start(array, element));
	else if (after >= array->elem_size)
		return (shift_and_insert(array, element));
	else
		return (grow_start(array, element));
}
