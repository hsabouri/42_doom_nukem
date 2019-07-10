/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:30:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/10 12:14:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_game			invert_button(t_game game, t_col_event *curr)
{
	t_entity	tmp;

	tmp = game.entities[curr->e_id];
	if (tmp.type <= CLOSE_PURPLE)
		game.entities[curr->e_id] = game.classes[tmp.type - 14 + 4 + 13];
	else
		game.entities[curr->e_id] = game.classes[tmp.type - 18 - 4 + 17];
	game.entities[curr->e_id].physic = tmp.physic;
	game.entities[curr->e_id].spawn = tmp.spawn;
	game.entities[curr->e_id].data = tmp.data;
	return (game);
}

static t_game	toggle_door(t_game game, t_col_event *curr)
{
	t_animation		anim;

	game.chunks = stack_sounds(game.chunks, 2, 0.5);
	anim.target = game.sectors[game.entities[curr->e_id].data].floor_b.z;
	anim.to_animate = &game.sectors[game.entities[curr->e_id].data].floor.z;
	apush(&game.animations, &anim);
	anim.target = game.sectors[game.entities[curr->e_id].data].ceiling_b.z;
	anim.to_animate = &game.sectors[game.entities[curr->e_id].data].ceiling.z;
	apush(&game.animations, &anim);
	game.sectors[game.entities[curr->e_id].data].ceiling_b =
		game.sectors[game.entities[curr->e_id].data].ceiling;
	game.sectors[game.entities[curr->e_id].data].floor_b =
		game.sectors[game.entities[curr->e_id].data].floor;
	game = invert_button(game, curr);
	return (game);
}

t_game			verify_card(t_game game, t_col_event *curr, t_player player)
{
	size_t			i;
	size_t			*c_entity;
	const t_entity	button = game.entities[curr->e_id];

	i = 0;
	while ((c_entity = (size_t *)anth(&player.inventory, i)))
	{
		if (game.entities[*c_entity].type == button.type - 9
			|| game.entities[*c_entity].type == button.type - 13)
			return (toggle_door(game, curr));
		i++;
	}
	return (game);
}
