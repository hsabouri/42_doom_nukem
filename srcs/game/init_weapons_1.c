/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:50:54 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/23 14:02:12 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_weapon	init_gun(t_img *textures)
{
	t_weapon	gun;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "init_gun");
	material = &textures[17];
	apush(&sprite, &material);
	material = &textures[18];
	apush(&sprite, &material);
	material = &textures[19];
	apush(&sprite, &material);
	gun = (t_weapon) {
		.name = W_GUN, .type = 1, .ammo = 12, .ammo_max = 12,
		.damage = 50, .cadence = 5, .type_shot = (t_shot_type)HITSCAN,
		.explosion = -1, .sprite = sprite, .decal = 200
	};
	return (gun);
}

static t_weapon	init_smg(t_img *textures)
{
	t_weapon	smg;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[20];
	apush(&sprite, &material);
	material = &textures[21];
	apush(&sprite, &material);
	material = &textures[22];
	apush(&sprite, &material);
	smg = ((t_weapon) {
		.name = W_SMG, .type = 1, .ammo = 30, .ammo_max = 30,
		.damage = 30, .cadence = 1, .type_shot = (t_shot_type)HITSCAN,
		.explosion = -1, .sprite = sprite, .decal = 250
	});
	return (smg);
}

static t_weapon	init_shotgun(t_img *textures)
{
	t_weapon	shotgun;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[23];
	apush(&sprite, &material);
	material = &textures[24];
	apush(&sprite, &material);
	material = &textures[25];
	apush(&sprite, &material);
	shotgun = ((t_weapon) {
		.name = W_SHOTGUN, .type = 1, .ammo = 10, .ammo_max = 10,
		.damage = 100, .cadence = 12, .type_shot = (t_shot_type)SHOTS,
		.explosion = -1, .sprite = sprite, .decal = 20
	});
	return (shotgun);
}

static t_weapon	init_revolver(t_img *textures)
{
	t_weapon	revolver;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[26];
	apush(&sprite, &material);
	material = &textures[27];
	apush(&sprite, &material);
	material = &textures[28];
	apush(&sprite, &material);
	revolver = ((t_weapon) {
		.name = W_REVOLVER, .type = 1, .ammo = 6, .ammo_max = 6,
		.damage = 90, .cadence = 8, .type_shot = (t_shot_type)HITSCAN,
		.explosion = -1, .sprite = sprite, .decal = 250
	});
	return (revolver);
}

t_weapon		*init_weapons(t_game *game)
{
	t_weapon *weapons;

	weapons = (t_weapon *)safe_malloc(sizeof(t_weapon) * 6, "init_weapons");
	weapons[0] = init_gun(game->textures);
	weapons[1] = init_smg(game->textures);
	weapons[2] = init_shotgun(game->textures);
	weapons[3] = init_revolver(game->textures);
	weapons[4] = init_nyan_gun(game->textures);
	weapons[5] = init_ammo(game->textures);
	game->nweapons = 6;
	return (weapons);
}
