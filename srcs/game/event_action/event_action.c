/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:36:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

static t_game	drop_entity_life(t_game game, t_player player, ssize_t t_id,
t_env *env)
{
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];
	t_entity		*entity;

	entity = &game.entities[t_id];
	if (entity->life <= weapon.damage)
	{
		if (entity->type == RACLURE)
			env->game_mode = WIN;
		game = delete_entity((size_t)t_id, game);
		game.chunks = stack_sounds(game.chunks, 0, 0.5);
	}
	else
	{
		entity->life -= weapon.damage;
		game.chunks = stack_sounds(game.chunks, 1, 0.5);
	}
	return (game);
}

static t_game	ammo_management(t_game game, t_player player, t_event *events)
{
	t_weapon	*weapon;
	t_weapon	*munitions;

	weapon = &game.weapons[player.weapons[player.equiped]];
	munitions = &game.weapons[player.secondary];
	if (player.is_shooting)
		weapon->ammo -= 1;
	if (weapon->ammo < weapon->ammo_max && munitions->ammo > 0
		&& events->keys[SDL_SCANCODE_R])
	{
		game.chunks = stack_sounds(game.chunks, 5, 0.5);
		munitions->ammo -= 1;
		weapon->ammo = weapon->ammo_max;
	}
	else if (weapon->ammo < weapon->ammo_max && munitions->ammo == 0
		&& events->keys[SDL_SCANCODE_R])
		game.chunks = stack_sounds(game.chunks, 3, 0.5);
	game.player = player;
	return (game);
}

static t_game	physic_interactions(t_game game, t_event *events,
t_player player, float span)
{
	t_col_event		*curr;
	t_entity		sub;

	while ((curr = (t_col_event *)apop(&game.col_events)))
	{
		if (curr->e_id < game.nentities)
		{
			sub = game.entities[curr->e_id];
			if (events->keys[SDL_SCANCODE_Q] && sub.type >= CLOSE_RED
				&& sub.type <= OPEN_PURPLE && game.animations.len == 0)
				game = verify_card(game, curr, player);
			else if (events->keys[SDL_SCANCODE_Q])
				game = pickup_object(game, curr);
			else if (sub.type >= GUN_MARINE && sub.type <= RED_MARINE)
				game.player = take_damage(game.player, sub, span);
		}
	}
	events->keys[SDL_SCANCODE_Q] = 0;
	return (game);
}

t_env			*event_action(t_env *env, t_event *events, u_int32_t *id_buf,
float span)
{
	t_selected	target;

	target = translate_out(id_buf[HEIGHT / 2 * WIDTH + WIDTH / 2]);
	env->game.player.is_shooting = is_shooting(&env->game, env->game.player,
		*events, env->game.frame);
	if (env->game.player.is_shooting)
		env->game = shooting_sound(env->game);
	env->game = ammo_management(env->game, env->game.player, events);
	if (target.type == PART_ENTITY && env->game.player.is_shooting
		&& env->game.entities[target.id].data > 0
		&& env->game.entities[target.id].type < 14)
		env->game = drop_entity_life(env->game, env->game.player, target.id,
		env);
	env->game = physic_interactions(env->game, events, env->game.player, span);
	if (env->game.player.my_entity.life <= 0)
		env->game_mode = DEAD;
	return (env);
}
