/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:57:34 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/31 13:45:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec3	set_speed(t_ph physic, t_event events, float old_timer)
{
	t_vec3	new_speed;

	new_speed = (t_vec3) {.z = physic.speed.z};
	if (events.keys[SDL_SCANCODE_A] || events.keys[SDL_SCANCODE_D])
		new_speed.x = (-physic.speed_max.x * events.keys[SDL_SCANCODE_A]
			+ physic.speed_max.x * events.keys[SDL_SCANCODE_D]) * (old_timer
			* SPEED_MULTIPLY);
	if (events.keys[SDL_SCANCODE_W] || events.keys[SDL_SCANCODE_S])
		new_speed.y = (-physic.speed_max.y * events.keys[SDL_SCANCODE_S]
			+ physic.speed_max.y * events.keys[SDL_SCANCODE_W]) * (old_timer
			* SPEED_MULTIPLY);
	if (physic.fly)
		new_speed.z = (-physic.speed_max.z * events.keys[SDL_SCANCODE_LCTRL]
			+ physic.speed_max.z * events.keys[SDL_SCANCODE_SPACE])
			* (old_timer * SPEED_MULTIPLY);
	new_speed = vec3_rot_z(new_speed, physic.look_h);
	return (new_speed);
}

static t_vec3	set_entity_speed(t_ph physic, t_ph player, float old_timer)
{
	t_vec3	new_speed;
	t_vec2	diff;
	float	dis;

	diff = vec2_sub(vec3_to_vec2(player.pos), vec3_to_vec2(physic.pos));
	new_speed = (t_vec3) {.z = physic.speed.z};
	dis = vec2_sq_size(diff);
	if (dis < physic.rad_inter * physic.rad_inter
		&& dis > physic.radius * physic.radius)
	{
		diff = vec2_scale(diff, vec2_inv_size(diff));
		new_speed = (t_vec3) {
			.x = diff.u * old_timer * SPEED_MULTIPLY * physic.speed_max.x / 2,
			.y = diff.v * old_timer * SPEED_MULTIPLY * physic.speed_max.y / 2,
			.z = new_speed.z};
	}
	return (new_speed);
}

static t_ph		entities_look_at(t_ph physic, t_ph player)
{
	t_vec2	diff;
	float	dis;
	float	sinus;
	float	cosin;

	diff = vec2_sub(vec3_to_vec2(player.pos), vec3_to_vec2(physic.pos));
	dis = vec2_sq_size(diff);
	if (dis < physic.rad_inter * physic.rad_inter)
	{
		diff = vec2_scale(diff, vec2_inv_size(diff));
		sinus = vec2_cross(diff, vec2_new(1, 0)).z;
		cosin = vec2_cross(diff, vec2_new(0, 1)).z;
		if (sinus >= 0)
			physic.look_h = atan(diff.v / diff.u);
		else
			physic.look_h = -1 + atan(diff.v / diff.u);
	}
	return (physic);
}

t_game			physic(t_game game, t_event events, float old_timer)
{
	t_game		new_game;
	t_ph		new_physic;
	size_t		i;

	i = 0;
	new_game = game;
	while (i < 1)
	{
		new_physic = game.entities[i].physic;
		// if (game.entities[i].damage >= 1)
		// 	new_physic.speed = set_entity_speed(new_physic,
		// 		game.player.my_entity.physic, old_timer);
		new_physic = entities_look_at(new_physic, game.player.my_entity.physic);
		new_game.entities[i].physic = entities_physic(new_physic, &game, i,
		old_timer);
		i++;
	}
	new_physic = game.player.my_entity.physic;
	new_physic.speed = set_speed(game.player.my_entity.physic, events,
		old_timer);
	new_game.player.my_entity.physic = entities_physic(new_physic, &game, -1,
		old_timer);
	new_game.log = game.log;
	return (new_game);
}
