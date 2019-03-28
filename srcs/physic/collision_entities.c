/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_entities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:39:14 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/04 16:39:15 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

u_int32_t	point_in_circle(t_ph entity_1, t_ph entity_2)
{
	float	d;

	d = (entity_1.pos.x - entity_2.pos.x) * (entity_1.pos.x - entity_2.pos.x) +
		(entity_1.pos.y - entity_2.pos.y) * (entity_1.pos.y - entity_2.pos.y);
	if (d <= entity_2.radius * entity_2.radius)
	{
		if (entity_1.pos.z > entity_2.pos.z + entity_2.height)
			return (0);
		return (1);
	}
	return (0);
}

float		circle_circle(t_ph entity_1, t_ph entity_2, t_col_mode col)
{
	float	d;

	d = (entity_1.pos.x - entity_2.pos.x) * (entity_1.pos.x - entity_2.pos.x) +
		(entity_1.pos.y - entity_2.pos.y) * (entity_1.pos.y - entity_2.pos.y);
	if ((d <= (entity_1.radius + entity_2.radius) * (entity_1.radius +
		entity_2.radius)) && col == COL_ENTITY)
	{
		if (entity_1.pos.z > entity_2.pos.z + entity_2.height)
			return (-1);
		return (d);
	}
	else if ((d <= (entity_1.rad_inter + entity_2.rad_inter) * (entity_1.rad_inter +
		entity_2.rad_inter)) && col == COL_INTERACT)
		return (d);
	return (-1);
}

int			interact(t_ph entity_1, t_ph entity_2)
{
	float	d;

	d = circle_circle(entity_1, entity_2, COL_INTERACT);
	if (d != -1)
		return (1);
	return (0);
}