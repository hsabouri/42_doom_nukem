/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:28:03 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/11 19:17:08 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <load_save.h>
#include <doom.h>

// remettre ca dans libsave/sources
inline size_t	id_from_p(void *ptr, void *tab, size_t size)
{
	return ((ptr - tab) / size);
}

inline void		*id_to_p(ssize_t index, void *tab, size_t size)
{
	return (tab + index * size);
}
