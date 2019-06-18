/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/18 14:22:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>

t_env	*event_action(t_env *env, t_event events, u_int32_t *id_buf)
{
	const t_selected	target = translate_out(
		id_buf[HEIGHT / 2 * WIDTH + WIDTH / 2]);
	t_entity	*curr;

	if (target.type == PART_ENTITY)
	{
		if (target.type == PART_ENTITY && events.mouse[SDL_BUTTON_LEFT]
			&& env->game.entities[target.id].damage > 0)
		{
			// env.game = drop_entity_life(env.game, env.game.player, target.id);
		}
		else if (target.type == PART_ENTITY && events.keys[SDL_SCANCODE_E]
			&& env->game.entities[target.id].type == BUTTON)
		{
			// env.game.animations = animate_door(env.game, target.id, env.game.player); // player to check if correct id is in
		}
	}
	//return (pickup_actions());
	return (env);
}
