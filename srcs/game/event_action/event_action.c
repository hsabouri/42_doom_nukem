/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/23 16:06:09 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_game			add_dying_entities(t_game game, t_entity *entity, size_t e_num)
{
	t_dying_entity d_entity;

	d_entity.dying_entity = entity;
	if (entity->type == GUN_MARINE)
	{
		d_entity.replace_entity = game.e
	}

}

static t_game	drop_entity_life(t_game game, t_player player, ssize_t t_id)
{
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];
	t_entity		*entity;

	entity = &game.entities[t_id];
	if (entity->life <= weapon.damage)
	{
		//del
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
		game.chunks = stack_sounds(game.chunks, 3, 0.5);
		munitions->ammo -= 1;
		weapon->ammo = weapon->ammo_max;
	}
	else if (weapon->ammo < weapon->ammo_max && munitions->ammo == 0
		&& events->keys[SDL_SCANCODE_R])
		game.chunks = stack_sounds(game.chunks, 9, 0.5);
	game.player = player;
	return (game);
}

t_game			physic_interactions(t_game game, t_event *events, t_player player)
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
		}
	}
	return (game);
}

t_env			*event_action(t_env *env, t_event *events, u_int32_t *id_buf)
{
	const t_selected	target = translate_out(
		id_buf[HEIGHT / 2 * WIDTH + WIDTH / 2]);

	env->game.player.is_shooting = is_shooting(&env->game, env->game.player,
		*events, env->game.frame);
	if (env->game.player.is_shooting)
		env->game = shooting_sound(env->game);
	env->game = ammo_management(env->game, env->game.player, events);
	if (target.type == PART_ENTITY && env->game.player.is_shooting
		&& env->game.entities[target.id].data > 0
		&& env->game.entities[target.id].type < 14)
		env->game = drop_entity_life(env->game, env->game.player, target.id);
	env->game = physic_interactions(env->game, events, env->game.player);
	return (env);
}
