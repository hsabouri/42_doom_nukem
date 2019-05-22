/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:13:54 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/20 18:13:56 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_weapon	init_nyan_gun(t_img *textures)
{
	t_weapon	nyan_gun;
	t_array 	sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[39];
	apush(&sprite, &material);
	material = &textures[40];
	apush(&sprite, &material);
	material = &textures[41];
	apush(&sprite, &material);
	material = &textures[42];
	apush(&sprite, &material);
	material = &textures[43];
	apush(&sprite, &material);
	nyan_gun = ((t_weapon) {
		.name = (t_weapon_type)NYAN_GUN, .type = 1, .ammo = 100,
		.ammo_max = 100, .damage = 10000, .cadence = 30,
		.type_shot = (t_shot_type)SHOTS, .explosion = -1, .sprite = sprite,
		.decal = 15
	});
	return (nyan_gun);
}

t_weapon	init_grenade(t_img *textures)
{
	t_weapon	grenade;
	t_array 	sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[44];
	apush(&sprite, &material);
	material = &textures[45];
	apush(&sprite, &material);
	grenade = ((t_weapon) {
		.name = (t_weapon_type)GRENADE,	.type = 2, .ammo = 5, .ammo_max = 5,
		.damage = 50, .cadence = 20, .type_shot = (t_shot_type)SHOTS,
		.explosion = 1, .sprite = sprite, .decal = 200
	});
	return (grenade);
}

t_weapon	init_mine(t_img *textures)
{
	t_weapon	mine;
	t_array 	sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[46];
	apush(&sprite, &material);
	material = &textures[47];
	apush(&sprite, &material);
	mine = ((t_weapon) {
		.name = (t_weapon_type)MINE, .type = 2, .ammo = 5, .ammo_max = 5,
		.damage = 50, .cadence = 20, .type_shot = (t_shot_type)STATIC,
		.explosion = 2, .sprite = sprite, .decal = 0
	});
	return (mine);
}
