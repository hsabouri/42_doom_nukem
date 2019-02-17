/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:34:03 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/17 11:22:58 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./translate_id.h"

u_int32_t	translate_in(t_part part, t_mod mod, size_t id, char spare)
{
	u_int32_t	res;

	res = part;
	res += (u_int32_t)mod << ID_MOD_SHIFT;
	res += ((u_int32_t)spare & 0x7) << ID_SPARE_SHIFT;
	res += ((u_int32_t)id & 0xFFFFFF) << ID_ID_SHIFT;
	return (res);
}

t_selected	translate_out(u_int32_t serial)
{
	t_selected res;

	res.type = serial & ID_PART_MASK;
	res.mod = (serial & ID_MOD_MASK) >> ID_MOD_SHIFT;
	res.spare = (serial & ID_SPARE_MASK) >> ID_SPARE_SHIFT;
	res.id = (serial & ID_ID_MASK) >> ID_ID_SHIFT;
	return (res);
}
