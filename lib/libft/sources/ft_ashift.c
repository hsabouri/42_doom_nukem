/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ashift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:07:08 by hugo              #+#    #+#             */
/*   Updated: 2018/12/01 14:08:18 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ashift(t_array *array)
{
	array->first = array->first + array->elem_size;
	array->len -= 1;
	return (array->first);
}
