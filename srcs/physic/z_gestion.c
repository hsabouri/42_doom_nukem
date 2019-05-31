/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_gestion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:00:07 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/31 16:00:09 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

float	z_entity(t_sector sector, t_vec3 pos, int mode)
{
	float new_x;
	float new_y;
	float z;

	if (mode == 1)
	{
		new_x = pos.x - sector.center.u;
		new_y = pos.y - sector.center.v;
		z = new_x * sector.floor.x + new_y * sector.floor.y + sector.floor.z;
	}
	if (mode == 0)
	{
		new_x = pos.x - sector.center.u;
		new_y = pos.y - sector.center.v;
		z = new_x * sector.ceiling.x + new_y * sector.ceiling.y 
			+ sector.ceiling.z;
	}
	return (z);
}
