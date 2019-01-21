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
		new_speed.x = (-(2 + EPSILON) * events.keys[SDL_SCANCODE_D] + \
				(2 - EPSILON) * events.keys[SDL_SCANCODE_A]) / SPEED_REDUCE;
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
		new_speed.y = (-(2 + EPSILON) * events.keys[SDL_SCANCODE_S] + \
				(2 - EPSILON) * events.keys[SDL_SCANCODE_W]) / SPEED_REDUCE;
	if (player.physic.fly)
	{
		new_speed.z = (-(0.2 + EPSILON) * events.keys[SDL_SCANCODE_LSHIFT] + \
			(0.2 - EPSILON) * events.keys[SDL_SCANCODE_SPACE]);
	}
	new_speed = vec3_rot_z(new_speed, player.physic.look.u);
	return (new_speed);
}

t_vec3		z_move(t_ph *n_physic, t_game game)
{
	t_vec3		new_speed;
	float		delta;
	float		tmp;

	new_speed = n_physic->speed;
	delta = game.sectors[n_physic->sector_id].floor - n_physic->pos.z;
	if (n_physic->jump && game.sectors[n_physic->sector_id].floor - n_physic->pos.z == 0)
			new_speed.z = 0.2;
	if (delta < 0 && !n_physic->fly)
		new_speed.z -= (new_speed.z > MAX_FALL) ? n_physic->gravity : 0;  
	tmp = game.player.physic.pos.z + new_speed.z;
	new_speed = floor_col(tmp, game.sectors[n_physic->sector_id], new_speed);
	tmp = game.player.physic.pos.z + game.player.physic.height + new_speed.z;
	new_speed = ceil_col(tmp, game.sectors[n_physic->sector_id], new_speed);
	return (new_speed);
}

static t_vec3		teleportation(t_vec3 pos, t_game game, t_tp teleport, t_ph	*n_physic)
{
	t_vec2	diff;
	t_vec3	next_pos;
	float	delta_floor;
	float	delta_ceil;

	n_physic->sector_id = ((int)teleport.portal.from_wall == teleport.portal_in) ? \
				teleport.portal.to_sector : \
				teleport.portal.from_sector;
	delta_floor = game.sectors[n_physic->sector_id].floor - pos.z;
	delta_ceil = game.sectors[n_physic->sector_id].ceiling - (pos.z + n_physic->height);
	if (delta_floor >= 20 || delta_ceil < -0.0001)
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
		if (delta_floor >= 0 && delta_floor < 20)
			next_pos.z = pos.z + delta_floor;
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
	n_physic->speed = z_move(n_physic, game);
	next_pos = vec3_add(game.player.physic.pos, n_physic->speed);
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
	if ((n_player.physic.pos.z < game.sectors[n_player.physic.sector_id].floor + EPSILON && \
		n_player.physic.pos.z > game.sectors[n_player.physic.sector_id].floor - EPSILON) || \
		n_player.physic.fly)
	{
		n_player.physic.speed.z = 0;
		n_player.physic.jump = 0;

	}
	return (n_player);
}
