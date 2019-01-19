/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_physic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:52:28 by iporsenn          #+#    #+#             */
/*   Updated: 2018/12/21 17:52:30 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec3	set_speed(t_player player, t_event events)
{
	t_vec3	new_speed;

	new_speed.x = 0;
	new_speed.y = 0;
	new_speed.z = player.physic.speed.z;
	if (events.keys[SDL_SCANCODE_A] || events.keys[SDL_SCANCODE_D])
		new_speed.x = (-(1 + EPSILON) * events.keys[SDL_SCANCODE_D] + \
				(1 - EPSILON) * events.keys[SDL_SCANCODE_A]) / SPEED_REDUCE;
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
		new_speed.y = (-(1 + EPSILON) * events.keys[SDL_SCANCODE_S] + \
				(1 - EPSILON) * events.keys[SDL_SCANCODE_W]) / SPEED_REDUCE;
	new_speed = vec3_rot_z(new_speed, player.physic.look.u);
	return (new_speed);
}

t_ph		z_move(t_ph *n_physic, t_game game)
{
	t_ph		new_ph;
	float		delta;

	new_ph = *n_physic;
	delta = game.sectors[new_ph.sector_id].floor - new_ph.pos.z;
	if (delta < 0)
		new_ph.speed.z -= (new_ph.speed.z > MAX_FALL) ? new_ph.gravity : 0;  
	else
		new_ph.speed.z = 0;
	new_ph.pos = vec3_add(new_ph.pos, new_ph.speed);
	new_ph.pos = floor_col(new_ph.pos, game.sectors[new_ph.sector_id], new_ph.speed, game);
	return (new_ph);
}

static t_vec3		teleportation(t_vec3 pos, t_game game, t_tp teleport, t_ph	*n_physic)
{
	t_vec2	diff;
	t_vec3	next_pos;
	float	delta;

	n_physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in) ? \
				teleport.portal.to_sector : \
				teleport.portal.from_sector;
	delta = game.sectors[n_physic->sector_id].floor - pos.z;
	if (delta >= 20)
	{
		n_physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in) ? \
			teleport.portal.from_sector : \
			teleport.portal.to_sector;
		n_physic->speed.x = 0;
		n_physic->speed.y = 0;
	}
	else
	{
		next_pos = pos;
		diff = vec2_sub(game.points[teleport.to_wall.a], game.points[teleport.from_wall.a]);
		next_pos.x = pos.x + diff.u;
		next_pos.y = pos.y + diff.v;
		next_pos.z = pos.z + delta;
		return (next_pos);
	}
	return (pos);
}

static t_vec3	move_player(t_ph *n_physic, t_game game, t_event events, int wall)
{
	t_vec3		next_pos;
	int			col;
	t_tp		teleport;

	n_physic->pos = vec3_add(game.player.physic.pos, n_physic->speed);
	*n_physic = z_move(n_physic, game);
	next_pos = n_physic->pos;
	col = collision(next_pos, game, &n_physic->sector_id, wall);
	if (events.keys[SDL_SCANCODE_C] == 0)
	{
		if (col >= 0)
		{
			if (game.walls[col].portal == -1)
				return (game.player.physic.pos); //CAUTION
			else
			{
				teleport.portal = game.portals[game.walls[col].portal];
				teleport.portal_in = col;
				teleport.from_wall = game.walls[col];
				teleport.to_wall = ((int)teleport.portal.to_wall == col) ? \
						game.walls[teleport.portal.from_wall] : \
						game.walls[teleport.portal.to_wall];
				teleport.portal_out = ((int)teleport.portal.from_wall == col) ? \
						teleport.portal.to_wall : teleport.portal.from_wall;
				game.player.physic.pos = teleportation(game.player.physic.pos, game, teleport, \
											n_physic);
				return (move_player(n_physic, game, events, teleport.portal_out));
			}
		}
	}
	else
		return (next_pos);
	return (next_pos);
}

t_player		player_physic(t_event events, t_game game)
{
	t_player	n_player;
	
	n_player = game.player;
	n_player.physic.speed = set_speed(game.player, events);
	n_player.physic.pos = move_player(&n_player.physic, game, events, -1);
	n_player.physic.speed.x = 0;
	n_player.physic.speed.y = 0;
	if (n_player.physic.pos.z == game.sectors[n_player.physic.sector_id].floor)
		n_player.physic.speed.z = 0;
	return (n_player);
}
