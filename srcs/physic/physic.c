/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:57:34 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/25 17:03:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec3	set_speed(t_ph physic, t_event events)
{
	t_vec3	new_speed;

	new_speed.x = 0;
	new_speed.y = 0;
	new_speed.z = physic.speed.z;
	if (events.keys[SDL_SCANCODE_A] || events.keys[SDL_SCANCODE_D])
	{
		new_speed.x = (-physic.speed_max.x * events.keys[SDL_SCANCODE_A]
			+ physic.speed_max.x * events.keys[SDL_SCANCODE_D]) /
			(float)SPEED_REDUCE;
	}
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
		new_speed.y = (-physic.speed_max.y * events.keys[SDL_SCANCODE_S]
		+ physic.speed_max.y * events.keys[SDL_SCANCODE_W]) /
		(float)SPEED_REDUCE;
	if (physic.fly)
	{
		new_speed.z = (-physic.speed_max.z * events.keys[SDL_SCANCODE_LCTRL]
		+ physic.speed_max.z * events.keys[SDL_SCANCODE_SPACE]) /
		(float)SPEED_REDUCE;
	}
	new_speed = vec3_rot_z(new_speed, physic.look_h);
	return (new_speed);
}

t_game			physic(t_game game, t_event events)
{
	t_game		new_game;
	t_ph		new_physic;

	new_game = game;
	new_physic = game.player.physic;
	new_physic.speed = set_speed(game.player.physic, events);
	new_game.player.physic = entities_physic(new_physic, game);
	return (new_game);
}
