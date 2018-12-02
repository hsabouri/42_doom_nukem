/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ashift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:07:08 by hugo              #+#    #+#             */
/*   Updated: 2018/12/02 20:41:38 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ashift(t_array *array)
{
	void	*elem;

	if (!array)
		return (NULL);
	if (array->len < 1)
		return (NULL);
	
	elem = array->first;
	if (array->len == 1)
		array->first = array->mem;
	else
		array->first = array->first + array->elem_size;
	array->len -= 1;
	return (elem);
}
