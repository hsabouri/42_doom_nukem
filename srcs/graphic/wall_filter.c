/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:29:26 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/19 19:07:35 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./graphic_project.h"

void			build_rays(t_vec2 rays[2], t_ph physic, t_vec2 a, t_vec2 b)
{
	const float		x_start = PWIDTH / 2;
	t_vec2			tmp;
	const t_vec2	v_rays[2] = {
		vec2_rot((t_vec2){-x_start, PDIS}, physic.look_h),
		vec2_rot((t_vec2){x_start, PDIS}, physic.look_h)
	};

	rays[0] = vec2_sub(a, vec3_to_vec2(physic.pos));
	rays[1] = vec2_sub(b, vec3_to_vec2(physic.pos));
	if (vec2_cross(rays[0], rays[1]).z > 0)
	{
		tmp = rays[0];
		rays[0] = rays[1];
		rays[1] = tmp;
	}
	if (vec2_cross(v_rays[0], rays[0]).z >= 0)
		rays[0] = v_rays[0];
	if (vec2_cross(v_rays[1], rays[1]).z <= 0)
		rays[1] = v_rays[1];
}

t_bunch			filter(t_game game, t_sector sector, t_vec2 r[2], t_vec2 pos, ssize_t mask)
{
	t_bunch		res;
	t_i_wall	current;
	t_wall		wall;
	t_vec2		a;
	t_vec2		b;

	res.sector = sector;
	current.wall_id = sector.start;
	res.nwalls = 0;
	printf("Retained walls of sector %zu:\n", sector.sector_id);
	while (current.wall_id < sector.start + sector.number)
	{
		wall = game.walls[current.wall_id];
		a = vec2_sub(game.points[wall.a], pos);
		b = vec2_sub(game.points[wall.b], pos);
		if ((size_t)mask != current.wall_id && ((vec2_cross(r[0], a).z <= 0 && vec2_cross(r[1], a).z >= 0) ||
			(vec2_cross(r[0], b).z <= 0 && vec2_cross(r[1], b).z >= 0)))
		{
			current.a = vec2_to_fvec2(game.points[wall.a]);
			current.b = vec2_to_fvec2(game.points[wall.b]);
			res.walls[res.nwalls] = current;
			printf("	%zu\n", current.wall_id);
			++res.nwalls;
		}
		++current.wall_id;
	}
	return (res);
}
