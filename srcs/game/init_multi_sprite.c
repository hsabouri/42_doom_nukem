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

static t_array	sprite_1(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 8, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[5];
	apush(&sprite, &material);
	material = &mats[6];
	apush(&sprite, &material);
	material = &mats[7];
	apush(&sprite, &material);
	material = &mats[8];
	apush(&sprite, &material);
	material = &mats[9];
	apush(&sprite, &material);
	material = &mats[10];
	apush(&sprite, &material);
	material = &mats[11];
	apush(&sprite, &material);
	material = &mats[12];
	apush(&sprite, &material);
	return (sprite);
}

static t_array	sprite_2(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[13];
	apush(&sprite, &material);
	return (sprite);
}

static t_array	sprite_3(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 8, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[14];
	apush(&sprite, &material);
	material = &mats[15];
	apush(&sprite, &material);
	material = &mats[16];
	apush(&sprite, &material);
	material = &mats[17];
	apush(&sprite, &material);
	material = &mats[18];
	apush(&sprite, &material);
	material = &mats[19];
	apush(&sprite, &material);
	material = &mats[20];
	apush(&sprite, &material);
	material = &mats[21];
	apush(&sprite, &material);
	return (sprite);
}

static t_array	sprite_4(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 8, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[22];
	apush(&sprite, &material);
	material = &mats[23];
	apush(&sprite, &material);
	material = &mats[24];
	apush(&sprite, &material);
	material = &mats[25];
	apush(&sprite, &material);
	material = &mats[26];
	apush(&sprite, &material);
	material = &mats[27];
	apush(&sprite, &material);
	material = &mats[28];
	apush(&sprite, &material);
	material = &mats[29];
	apush(&sprite, &material);
	return (sprite);
}

t_array			*init_multi_sprite(t_game *game, t_mat *mats)
{
	t_array *multi_sprite;

	multi_sprite = (t_array *)safe_malloc(sizeof(t_array) * 13,
		"init_multi_sprite");
	multi_sprite[0] = sprite_1(mats);
	multi_sprite[1] = sprite_2(mats);
	multi_sprite[2] = sprite_3(mats);
	multi_sprite[3] = sprite_4(mats);
	multi_sprite[4] = sprite_5(mats);
	multi_sprite[5] = sprite_6(mats);
	multi_sprite[6] = sprite_7(mats);
	multi_sprite[7] = sprite_8(mats);
	multi_sprite[8] = sprite_9(mats);
	multi_sprite[9] = sprite_10(mats);
	multi_sprite[10] = sprite_11(mats);
	multi_sprite[11] = sprite_12(mats);
	multi_sprite[12] = sprite_13(mats);
	game->nmulti_mats = 13;
	return (multi_sprite);
}
