/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_inner_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:21:02 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/07 19:30:02 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*array_open(void *ptr, size_t loc, size_t size, size_t elem_size)
{
	void	*new_ptr;

	if (loc > size)
		return (NULL);
	new_ptr = (void *)malloc(elem_size * (size + 1));
	ft_memmove(new_ptr, ptr, elem_size * loc);
	if (loc < size)
		ft_memmove(new_ptr + (elem_size * (loc + 1)), ptr + (elem_size * loc),\
			(size - loc) * elem_size);
	free(ptr);
	return (new_ptr);
}

void	*array_close(void *ptr, size_t loc, size_t size, size_t elem_size)
{
	void	*new_ptr;

	if (loc >= size)
		return (NULL);
	new_ptr = (void *)malloc(elem_size * (size - 1));
	ft_memmove(new_ptr, ptr, elem_size * loc);
	ft_memmove(new_ptr + (elem_size * loc), ptr + (elem_size * (loc + 1)),\
		(size - 1 - loc) * elem_size);
	free(ptr);
	return (new_ptr);
}

void	*array_open_swap(void *ptr, size_t loc1, size_t loc2, size_t elem_size)
{
	ft_memmove(ptr + (loc1 + 1) * elem_size, ptr + loc1 * elem_size,
		(loc2 - loc1) * elem_size);
	return (ptr);
}
