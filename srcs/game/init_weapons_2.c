/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:13:54 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/22 18:07:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_weapon	init_nyan_gun(t_img *textures)
{
	t_weapon	nyan_gun;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[29];
	apush(&sprite, &material);
	material = &textures[30];
	apush(&sprite, &material);
	material = &textures[31];
	apush(&sprite, &material);
	nyan_gun = ((t_weapon) {
		.name = (t_weapon_type)NYAN_GUN, .type = 1, .ammo = 100,
		.ammo_max = 100, .damage = 10000, .cadence = 5,
		.type_shot = (t_shot_type)SHOTS, .explosion = -1, .sprite = sprite,
		.decal = 15
	});
	return (nyan_gun);
}

t_weapon	init_ammo(t_img *textures)
{
	t_weapon	ammo;
	t_array		sprite;
	t_img		*material;

	sprite = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[34];
	apush(&sprite, &material);
	material = &textures[69];
	apush(&sprite, &material);
	ammo = ((t_weapon) {
		.name = (t_weapon_type)W_AMMO, .type = 2, .ammo = 5, .ammo_max = 5,
		.damage = 50, .cadence = 10, .type_shot = (t_shot_type)SHOTS,
		.explosion = 1, .sprite = sprite, .decal = 200
	});
	return (ammo);
}
