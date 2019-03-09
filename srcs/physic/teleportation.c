/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:10:04 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/23 14:10:05 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		set_tp(t_tp *teleport, t_touch touch, t_game game)
{
	teleport->portal = game.portals[game.walls[touch.wall].portal];
	teleport->portal_in = touch.wall;
	teleport->from_wall = game.walls[touch.wall];
	teleport->to_wall = ((int)teleport->portal.to_wall == touch.wall) ?
		game.walls[teleport->portal.from_wall] :
		game.walls[teleport->portal.to_wall];
	teleport->portal_out = ((int)teleport->portal.from_wall == touch.wall) ?
		teleport->portal.to_wall : teleport->portal.from_wall;
}

static void	if_not_tp(t_ph *physic, t_tp teleport)
{
	physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in)
		? teleport.portal.from_sector : teleport.portal.to_sector;
	physic->speed.x = 0;
	physic->speed.y = 0;
}

t_vec3		teleportation(t_vec3 pos, t_game game, t_tp teleport, t_ph *physic)
{
	t_vec2	diff;
	t_vec3	next_pos;
	float	delta_floor;
	float	delta_ceil;

	physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in)
		? teleport.portal.to_sector : teleport.portal.from_sector;
	delta_floor = game.sectors[physic->sector_id].floor - pos.z;
	delta_ceil = game.sectors[physic->sector_id].ceiling - pos.z;
	if (delta_floor >= 0.5 || delta_ceil < -0.0001)
		if_not_tp(physic, teleport);
	else
	{
		next_pos = pos;
		diff = vec2_sub(game.points[teleport.to_wall.a],
			game.points[teleport.from_wall.a]);
		next_pos.x = pos.x + diff.u;
		next_pos.y = pos.y + diff.v;
		if (delta_floor >= 0 || delta_floor > -0.5)
			next_pos.z = pos.z + delta_floor;
		return (next_pos);
	}
	return (pos);
}