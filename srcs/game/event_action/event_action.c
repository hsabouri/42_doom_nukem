/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/22 20:20:58 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

static t_game	drop_entity_life(t_game game, t_player player, ssize_t t_id)
{
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];
	t_entity		*entity;

	entity = &game.entities[t_id];
	if (entity->life <= weapon.damage)
	{
		game = delete_entity((size_t)t_id, game);
		game.chunks = stack_sounds(game.chunks, 0, 0.1);
	}
	else
	{
		entity->life -= weapon.damage;
		game.chunks = stack_sounds(game.chunks, 1, 0.1);
	}
	return (game);
}
static int		is_shooting(t_game game, t_player player, t_event events,
size_t frame)
{
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];
	static size_t	last = 0;

	if (weapon.ammo == 0)
		return (0);
	if (frame - last > weapon.cadence && events.mouse[SDL_BUTTON_LEFT])
	{
		last = frame;
		return (1);
	}
	else
		return (0);

}

static t_player	ammo_management(t_game game, t_player player, t_event *events)
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
		munitions->ammo -= 1;
		weapon->ammo = weapon->ammo_max;
	}
	return (player);
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

	env->game.player.is_shooting = is_shooting(env->game, env->game.player,
		*events, env->game.frame);
	// push shooting sound
	env->game.player = ammo_management(env->game, env->game.player, events);
	if (target.type == PART_ENTITY && env->game.player.is_shooting
		&& env->game.entities[target.id].data > 0
		&& env->game.entities[target.id].type < 14)
		env->game = drop_entity_life(env->game, env->game.player, target.id);
	env->game = physic_interactions(env->game, events, env->game.player);
	return (env);
}
