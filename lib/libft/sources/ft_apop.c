/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:49:50 by hugo              #+#    #+#             */
/*   Updated: 2018/12/02 10:58:37 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*apop(t_array *array)
{
	void	*elem;
	
	if (array == NULL)
		return (NULL);
	if (array->len < 1)
		return (NULL);
	array->len--;
	elem = array->first + array->len * array->elem_size;
	return (elem);
}
