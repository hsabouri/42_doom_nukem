/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:30:22 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/10 14:07:37 by hsabouri         ###   ########.fr       */
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

t_array			*init_multi_sprite_2(t_array *multi_sprite,
t_mat *mats)
{
	multi_sprite[17] = sprite_2(mats, 50);
	multi_sprite[18] = sprite_2(mats, 51);
	multi_sprite[19] = sprite_2(mats, 52);
	multi_sprite[20] = sprite_2(mats, 53);
	multi_sprite[21] = sprite_2(mats, 54);
	multi_sprite[22] = sprite_2(mats, 55);
	multi_sprite[23] = sprite_2(mats, 56);
	multi_sprite[24] = sprite_1(mats, 57, 58);
	multi_sprite[25] = sprite_2(mats, 59);
	multi_sprite[26] = sprite_2(mats, 60);
	multi_sprite[27] = sprite_2(mats, 61);
	multi_sprite[28] = sprite_2(mats, 62);
	multi_sprite[29] = sprite_2(mats, 63);
	multi_sprite[30] = sprite_2(mats, 64);
	multi_sprite[31] = sprite_2(mats, 65);
	multi_sprite[32] = sprite_2(mats, 66);
	multi_sprite[33] = sprite_2(mats, 67);
	return (multi_sprite);
}

t_array			*init_multi_sprite(t_game *game, t_mat *mats)
{
	t_array *multi_sprite;

	game->nmulti_mats = 34;
	multi_sprite = (t_array *)safe_malloc(sizeof(t_array)
		* game->nmulti_mats, "init_multi_sprite");
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
	multi_sprite[13] = sprite_2(mats, 46);
	multi_sprite[14] = sprite_2(mats, 47);
	multi_sprite[15] = sprite_2(mats, 48);
	multi_sprite[16] = sprite_2(mats, 49);
	return (init_multi_sprite_2(multi_sprite, mats));
}
