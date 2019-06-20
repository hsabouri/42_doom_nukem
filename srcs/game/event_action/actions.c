/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:30:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/20 14:58:24 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_game	invert_button(t_game game, t_col_event *curr)
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

t_game	pickup_object(t_game game, t_col_event *curr)
{
	t_entity		sub;
	t_entity		*sub_to_push;

	sub = game.entities[curr->e_id];
	if (sub.type >= RED_KEY_CARD && sub.type <= PURPLE_KEY_CARD
		&& sub.physic.radius > 0)
	{
		sub_to_push = &game.entities[curr->e_id];
		apush(&game.player.inventory, &sub_to_push);
		game.entities[curr->e_id].physic.radius = 0;
		game.entities[curr->e_id].physic.rad_inter = 0;
	}
	else if (sub.type >= APPLE && sub.type <= MEDIPACK)
	{
		game.player.my_entity.life -= sub.data;
		if (game.player.my_entity.life > 100)
			game.player.my_entity.life = 100;
		game = delete_entity(curr->e_id, game);
	}
	return (game);
}
