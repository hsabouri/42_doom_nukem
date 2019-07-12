/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:57:34 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/12 13:42:31 by hsabouri         ###   ########.fr       */
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
		&& dis > physic.radius * physic.radius * 4)
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
	t_vec2	vec;
	t_vec2	abs_vec;
	float	tang;
	float	dis;

	vec = vec2_sub(vec3_to_vec2(player.pos), vec3_to_vec2(physic.pos));
	dis = vec2_sq_size(vec);
	if (dis < physic.rad_inter * physic.rad_inter)
	{
		abs_vec = vec2_new(fabs(vec.u), fabs(vec.v));
		if ((vec.u > 0 && vec.v > 0) || (vec.u < 0 && vec.v < 0))
			tang = abs_vec.u / abs_vec.v;
		else
			tang = abs_vec.v / abs_vec.u;
		if (vec.u > 0 && vec.v > 0)
			physic.look_h = -(atan(tang)) + 0.6;
		else if (vec.u > 0 && vec.v < 0)
			physic.look_h = -(atan(tang) + 0.5 * M_PI) + 0.6;
		else if (vec.u < 0 && vec.v < 0)
			physic.look_h = -(atan(tang) + M_PI) + 0.6;
		else
			physic.look_h = -(atan(tang) + 1.5 * M_PI) + 0.6;
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
	while (i < game.nentities)
	{
		new_physic = game.entities[i].physic;
		if (game.entities[i].data >= 1)
			new_physic.speed = set_entity_speed(new_physic,
				game.player.my_entity.physic, old_timer);
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
	new_game.col_events = game.col_events;
	return (new_game);
}
