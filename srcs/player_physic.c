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
		new_speed.x = (-(3 + FLT_EPSILON) * events.keys[SDL_SCANCODE_A] + \
				(3 - FLT_EPSILON) * events.keys[SDL_SCANCODE_D]) / SPEED_REDUCE;
	}
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
	{
		new_speed.y = (-(3 + FLT_EPSILON) * events.keys[SDL_SCANCODE_S] + \
				(3 - FLT_EPSILON) * events.keys[SDL_SCANCODE_W]) / SPEED_REDUCE;
	}
	if (events.keys[SDL_SCANCODE_LSHIFT] || events.keys[SDL_SCANCODE_LCTRL])
	{
		new_speed.z = (-(3 + FLT_EPSILON) * events.keys[SDL_SCANCODE_LCTRL] + \
		(3 - FLT_EPSILON) * events.keys[SDL_SCANCODE_LSHIFT]) / SPEED_REDUCE;
	}
	// if (events.keys[SDL_SCANCODE_SPACE] && !events.keys[SDL_SCANCODE_LSHIFT] \
	// 	&& CollisionFloor == 1)
	// 	new_speed.z = (5 - FLT_EPSILON) * events.keys[SDL_SCANCODE_SPACE];
	new_speed = vec3_rot_z(new_speed, player.physic.look.u);
	return (new_speed);
}

static t_vec3	move_player(t_vec3 speed, t_game game)
{
	t_vec3		next_pos;

	next_pos = vec3_add(game.player.physic.pos, speed);
	if (collision(next_pos, game) == 1)
		return (game.player.physic.pos);
	else
		return (next_pos);
}

// t_vec2			teleportation(t_player player, t_portal portal1, \
// 												t_portal portal2, t_game game)
// {
// 	t_vec2	next_pos;
//
// 	next_pos.x = game.points.[portal2.a].u - game.points[portal1.a].u + FLT_EPSILON;
// 	next_pos.y = game.points.[portal2.a].v - game.points[portal1.a].v + FLT_EPSILON;
// 	return (next_pos);
// }

t_player		player_physic(t_event events, t_game game)
{
	t_player	new_player;

	new_player = game.player;
	new_player.physic.speed = set_speed(game.player, events);
	new_player.physic.pos = move_player(new_player.physic.speed, game);
	new_player.physic.speed.x = 0;
	new_player.physic.speed.y = 0;
	new_player.physic.speed.z = 0;
	return (new_player);
}
