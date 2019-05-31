/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ashift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:07:08 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:36:18 by fmerding         ###   ########.fr       */
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
