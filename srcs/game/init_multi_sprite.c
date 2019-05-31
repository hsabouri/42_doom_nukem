/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:30:22 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/21 11:30:23 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_array	sprite_1(t_mat *mats, size_t first, size_t last)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 8, sizeof(t_mat *), "init_multi_sprite");
	while (first <= last)
	{
		material = &mats[first];
		apush(&sprite, &material);
		first++;
	}
	return (sprite);
}

static t_array	sprite_2(t_mat *mats, size_t id)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[id];
	apush(&sprite, &material);
	return (sprite);
}

t_array			*init_multi_sprite(t_game *game, t_mat *mats)
{
	t_array *multi_sprite;

	multi_sprite = (t_array *)safe_malloc(sizeof(t_array) * 13,
		"init_multi_sprite");
	multi_sprite[0] = sprite_1(mats, 5, 12);
	multi_sprite[1] = sprite_2(mats, 13);
	multi_sprite[2] = sprite_1(mats, 14, 21);
	multi_sprite[3] = sprite_1(mats, 22, 29);
	multi_sprite[4] = sprite_1(mats, 30, 37);
	multi_sprite[5] = sprite_2(mats, 38);
	multi_sprite[6] = sprite_2(mats, 39);
	multi_sprite[7] = sprite_2(mats, 40);
	multi_sprite[8] = sprite_2(mats, 41);
	multi_sprite[9] = sprite_2(mats, 42);
	multi_sprite[10] = sprite_2(mats, 43);
	multi_sprite[11] = sprite_2(mats, 44);
	multi_sprite[12] = sprite_2(mats, 45);
	game->nmulti_mats = 13;
	return (multi_sprite);
}
