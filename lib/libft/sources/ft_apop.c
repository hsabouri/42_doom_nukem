/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:49:50 by hugo              #+#    #+#             */
/*   Updated: 2019/04/02 16:01:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*apop(t_array *array)
{
	void	*elem;
	
	if (array == NULL)
		return (NULL);
	if (array->len == 0)
		return (NULL);
	array->len--;
	elem = array->first + array->len * array->elem_size;
	return (elem);
}
