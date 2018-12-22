/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anth.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:36:24 by hugo              #+#    #+#             */
/*   Updated: 2018/12/22 14:52:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*anth(const t_array *array, size_t index)
{
	if (array == NULL)
		return (NULL);
	if (array->first && index < array->len)
		return (array->first + index * array->elem_size);
	else
		return (NULL);
}
