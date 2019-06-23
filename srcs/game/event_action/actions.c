/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:30:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/23 18:16:06 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_game	loading_dying_entities(t_game game, float old_timer)
{
	int					i;
	t_dying_entity		*curr;
	t_array				new_array;
	ssize_t				del_ent;

	i = 0;
	del_ent = -1;
	new_array = safe_anew(NULL, 100, sizeof(t_dying_entity), "init");
	while ((curr = (t_dying_entity *)anth(&game.dying_entities, i)))
	{
		curr->time_left -= old_timer;
		if (curr->time_left <= 0 && del_ent == -1)
		{
			del_ent = curr->target_dying_entity;
		}
		else
		{
			apush(&new_array, curr);
		}
		i++;
	}
	free(game.dying_entities.mem);
	game.dying_entities = new_array;
	if (del_ent != -1)
		game = delete_entity(del_ent, game);
	return (game);
}

t_game	invert_sprite(t_game game, t_entity *entity, size_t new_id)
{
	t_entity	tmp;

	tmp = *entity;
	*entity = game.classes[new_id];
	entity->physic.pos = tmp.physic.pos;
	entity->spawn.pos = tmp.spawn.pos;
	entity->data = tmp.data;
	return (game);
}

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

t_game			invert_weapon(t_game game, t_col_event *curr, t_entity sub)
{
	t_entity	tmp;

	tmp = game.entities[curr->e_id];
	game.entities[curr->e_id] = game.classes[game.player.weapons[game.player.equiped] + 29];
	game.entities[curr->e_id].physic.pos = tmp.physic.pos;
	game.entities[curr->e_id].physic.fly = tmp.physic.fly;
	game.entities[curr->e_id].spawn.pos = tmp.spawn.pos;
	game.entities[curr->e_id].spawn.fly = tmp.spawn.fly;
	return (game);
}

t_game			pickup_object(t_game game, t_col_event *curr)
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
	else if (sub.type == AMMO && munitions->ammo < munitions->ammo_max)
	{
		game.chunks = stack_sounds(game.chunks, 11, 0.5);
		munitions->ammo += 1;
		game = delete_entity(curr->e_id, game);
	}
	else if (sub.type >= GUN && sub.type <= NYAN_GUN)
	{
		game.chunks = stack_sounds(game.chunks, 11, 0.5);
		game = invert_weapon(game, curr, sub);
		game.player.weapons[game.player.equiped] = sub.type - 30;
	}
	return (game);
}

static t_game	toggle_door(t_game game, t_col_event *curr)
{
	t_animation		anim;

	game.chunks = stack_sounds(game.chunks, 10, 0.5);
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
