/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <iporsenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:10:04 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/29 16:02:36 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			set_tp(t_tp *teleport, t_touch touch, t_game game)
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

static t_vec3	if_tp(t_vec3 pos, t_game *game, t_tp teleport)
{
	t_vec3	next_pos;
	t_vec2	diff;

	next_pos = pos;
	diff = vec2_sub(game->points[teleport.to_wall.a],
	game->points[teleport.from_wall.a]);
	next_pos.x = pos.x + diff.u;
	next_pos.y = pos.y + diff.v;
	return (next_pos);
}

static void		if_not_tp(t_ph *physic, t_tp teleport)
{
	physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in)
		? teleport.portal.from_sector : teleport.portal.to_sector;
	physic->speed.x = 0;
	physic->speed.y = 0;
}

t_vec3			teleportation(t_vec3 pos, t_game *game, t_tp teleport,
t_ph *physic)
{
	t_vec3		next_pos;
	t_trigger	tmp_log;
	float		delta_floor;
	float		delta_ceil;

	physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in)
		? teleport.portal.to_sector : teleport.portal.from_sector;
	delta_floor = game->sectors[physic->sector_id].floor.z - pos.z;
	delta_ceil = game->sectors[physic->sector_id].ceiling.z - pos.z;
	if (delta_floor >= 0.5 || delta_ceil < -0.0001)
		if_not_tp(physic, teleport);
	else
	{
		tmp_log.e_actif = game->player.my_entity;
		tmp_log.e_actif.physic.sector_id = physic->sector_id;
		tmp_log.condi = TRIGGER_SECTOR;
		tmp_log.e_passif = tmp_log.e_actif;
		apush(&game->log, &tmp_log);
		next_pos = if_tp(pos, game, teleport);
		if (delta_floor >= 0 || delta_floor > -0.5)
			next_pos.z = pos.z + delta_floor;
		return (next_pos);
	}
	return (pos);
}
