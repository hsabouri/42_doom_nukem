/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:28:03 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/16 14:28:08 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

inline size_t	id_from_p(void *ptr, void *tab, size_t size)
{
	return ((ptr - tab) / size);
}

inline void		*id_to_p(ssize_t index, void *tab, size_t size)
{
	return (tab + index * size);
}
