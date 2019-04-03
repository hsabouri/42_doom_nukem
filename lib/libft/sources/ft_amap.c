/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:02:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/29 12:10:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_array		amap(t_array *array, void *(*f)(void *), size_t new_elem_size)
{
	t_array	ret;
	size_t	current;
	void	*to_copy;

	if (!array)
		return ((t_array) {.mem = NULL, .len = 0});
	ret = anew(NULL, array->len, new_elem_size);
	current = 0;
	while (current < array->len)
	{
		to_copy = (*f)(array->first + current * array->elem_size);
		apush(&ret, to_copy);
		free(to_copy);
		current++;
	}
	return (ret);
}

t_array		amapi_state(t_array *array, void *(*f)(void *, void *, size_t),
void *state, size_t new_elem_size)
{
	t_array	ret;
	size_t	current;
	void	*to_copy;

	if (!array)
		return ((t_array) {.mem = NULL, .len = 0});
	ret = anew(NULL, array->len, new_elem_size);
	current = 0;
	while (current < array->len)
	{
		to_copy = (*f)(array->first + current * array->elem_size, state,
			current);
		apush(&ret, to_copy);
		free(to_copy);
		current++;
	}
	return (ret);
}
