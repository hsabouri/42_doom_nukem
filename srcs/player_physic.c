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
	new_speed.z = 0;
	if (events.keys[SDL_SCANCODE_A] || events.keys[SDL_SCANCODE_D])
	{
		new_speed.x = (-(3 + EPSILON) * events.keys[SDL_SCANCODE_D] + \
				(3 - EPSILON) * events.keys[SDL_SCANCODE_A]) / SPEED_REDUCE;
	}
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
	{
		new_speed.y = (-(3 + EPSILON) * events.keys[SDL_SCANCODE_S] + \
				(3 - EPSILON) * events.keys[SDL_SCANCODE_W]) / SPEED_REDUCE;
	}
	if (events.keys[SDL_SCANCODE_SPACE] || events.keys[SDL_SCANCODE_LCTRL])
	{
		new_speed.z = (-(3 + EPSILON) * events.keys[SDL_SCANCODE_LCTRL] + \
		(3 - EPSILON) * events.keys[SDL_SCANCODE_SPACE]) / SPEED_REDUCE;
	}
	// if (events.keys[SDL_SCANCODE_SPACE] && !events.keys[SDL_SCANCODE_LSHIFT] \
	// 	&& CollisionFloor == 1)
	// 	new_speed.z = (5 - EPSILON) * events.keys[SDL_SCANCODE_SPACE];
	new_speed = vec3_rot_z(new_speed, player.physic.look.u);
	return (new_speed);
}

static t_vec3		teleportation(t_vec3 pos, t_game game, t_tp teleport, u_int32_t *sector_id)
{
	t_vec2	diff;
	t_vec3	next_pos;

	diff = vec2_sub(game.points[teleport.to_wall.a], game.points[teleport.from_wall.a]);
	next_pos.x = pos.x + diff.u;
	next_pos.y = pos.y + diff.v;
	*sector_id = ((int)teleport.portal.from_wall == teleport.portal_in) ? \
					teleport.portal.to_sector : \
					teleport.portal.from_sector;
	next_pos.z = game.sectors[*sector_id].floor;
	return (pos);
}

static t_vec3	move_player(t_ph *n_physic, t_game game, t_event events, int wall)
{
	t_vec3		next_pos;
	int			col;
	t_tp		teleport;

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
				game.player.physic.pos = teleportation(game.player.physic.pos, game, teleport, &n_physic->sector_id);
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
	n_player.physic.speed.z = 0;
	return (n_player);
}
