/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 12:56:13 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/10 12:34:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_game		invert_weapon(t_game game, t_col_event *curr)
{
	t_entity	tmp;

	tmp = game.entities[curr->e_id];
	game.entities[curr->e_id] = game.classes[
		game.player.weapons[game.player.equiped] + 29];
	game.entities[curr->e_id].physic.pos = tmp.physic.pos;
	game.entities[curr->e_id].physic.fly = tmp.physic.fly;
	game.entities[curr->e_id].spawn.pos = tmp.spawn.pos;
	game.entities[curr->e_id].spawn.fly = tmp.spawn.fly;
	return (game);
}

t_game		pickup_object2(t_game game, t_col_event *curr, t_entity sub,
t_weapon *munitions)
{
	if (sub.type == AMMO && munitions->ammo < munitions->ammo_max)
	{
		game.chunks = stack_sounds(game.chunks, 3, 0.5);
		munitions->ammo += 1;
		game = delete_entity(curr->e_id, game);
	}
	else if (sub.type >= GUN && sub.type <= NYAN_GUN)
	{
		game.chunks = stack_sounds(game.chunks, 3, 0.5);
		game = invert_weapon(game, curr);
		game.player.weapons[game.player.equiped] = sub.type - 30;
	}
	return (game);
}

t_game		pickup_object(t_game game, t_col_event *curr)
{
	t_entity		sub;
	t_entity		*sub_to_push;
	t_weapon		*munitions;

	sub = game.entities[curr->e_id];
	munitions = &game.weapons[game.player.secondary];
	if (sub.type >= RED_KEY_CARD && sub.type <= PURPLE_KEY_CARD
		&& sub.physic.radius > 0 && game.player.inventory.len < 5)
	{
		sub_to_push = &game.entities[curr->e_id];
		apush(&game.player.inventory, &curr->e_id);
		game.entities[curr->e_id].physic.radius = 0;
		game.entities[curr->e_id].physic.rad_inter = 0;
	}
	else if (sub.type >= APPLE && sub.type <= MEDIPACK
		&& game.player.my_entity.life < 100)
	{
		game.player.my_entity.life -= sub.data;
		if (game.player.my_entity.life > 100)
			game.player.my_entity.life = 100;
		game = delete_entity(curr->e_id, game);
	}
	return (pickup_object2(game, curr, sub, munitions));
}
