/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anth.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:36:24 by hugo              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/12/21 15:01:09 by hsabouri         ###   ########.fr       */
=======
/*   Updated: 2018/12/20 15:58:58 by hsabouri         ###   ########.fr       */
>>>>>>> something is displayed...
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
