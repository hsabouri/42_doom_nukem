/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anth.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:36:24 by hugo              #+#    #+#             */
/*   Updated: 2018/12/03 10:03:55 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*anth(t_array *array, size_t index)
{
	if (array == NULL)
		return (NULL);
	if (array->first && index < array->len)
		return (array->first + array->len * array->elem_size);
}
