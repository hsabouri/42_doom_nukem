/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/18 16:52:03 by hsabouri         ###   ########.fr       */
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
		// push death sound
	}
	else
	{
		entity->life -= weapon.damage;
		// push hurt sound
	}
	return (game);
}

static int		is_shooting(t_game game, t_player player, t_event events,
size_t frame)
{
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];
	static size_t	last = 0;

	if (frame - last > weapon.cadence && events.mouse[SDL_BUTTON_LEFT])
	{
		// push shooting sound
		last = frame;
		return (1);
	}
	else
		return (0);

}

t_game			physic_interactions(t_game game, t_event events, t_player player)
{
	t_col_event		*curr;
	t_animation		anim;

	while ((curr = (t_col_event *)apop(&game.col_events)))
	{
		if (events.keys[SDL_SCANCODE_E] &&
			game.entities[curr->e_id].type >= BUTTON)
		{
			anim.target = game.sectors[game.entities[curr->e_id].damage].floor_b.z;
			anim.to_animate = &game.sectors[game.entities[curr->e_id].damage].floor.z;
			apush(&game.animations, &anim);
			anim.target = game.sectors[game.entities[curr->e_id].damage].ceiling_b.z;
			anim.to_animate = &game.sectors[game.entities[curr->e_id].damage].ceiling.z;
			apush(&game.animations, &anim);
		}
	}
	return (game);
}

t_env			*event_action(t_env *env, t_event events, u_int32_t *id_buf)
{
	const t_selected	target = translate_out(
		id_buf[HEIGHT / 2 * WIDTH + WIDTH / 2]);
	t_entity	*curr;

	env->game.player.is_shooting = is_shooting(env->game, env->game.player,
		events, env->game.frame);
	if (target.type == PART_ENTITY && env->game.player.is_shooting
		&& env->game.entities[target.id].damage > 0
		&& env->game.entities[target.id].type < 14)
		env->game = drop_entity_life(env->game, env->game.player, target.id);
	env->game = physic_interactions(env->game, events, env->game.player);
	return (env);
}