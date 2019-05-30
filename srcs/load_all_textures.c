/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:07:49 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/14 18:07:50 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_img	*load_all_textures(t_game *game)
{
	t_img	*textures;

	textures = (t_img *)safe_malloc(38 * sizeof(t_img), "textures");
	textures[0] = parse_tga("./textures/wall.tga", 1);
	textures[1] = parse_tga("./textures/floor.tga", 1);
	textures[2] = parse_tga("./textures/items/key_card.tga", 1);
	textures[3] = parse_tga("./textures/skybox.tga", 1);
	textures[4] = parse_tga("./textures/fence.tga", 1);
	textures[5] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine0.tga", 0);
	textures[6] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine1.tga", 0);
	textures[7] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine2.tga", 0);
	textures[8] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine3.tga", 0);
	textures[9] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine4.tga", 0);
	textures[10] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine5.tga", 0);
	textures[11] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine6.tga", 0);
	textures[12] = parse_tga("./textures/multi_sprite/gun_marine/gun_marine7.tga", 0);
	textures[13] = parse_tga("./textures/hud/cross.tga", 0);
	textures[14] = parse_tga("./textures/hud/full_life.tga", 0);
	textures[15] = parse_tga("./textures/hud/empty_life.tga", 0);
	textures[16] = parse_tga("./textures/hud/help.tga", 0);
	textures[17] = parse_tga("./textures/weapons/gun/gun0.tga", 0);
	textures[18] = parse_tga("./textures/weapons/gun/gun1.tga", 0);
	textures[19] = parse_tga("./textures/weapons/gun/gun2.tga", 0);
	textures[20] = parse_tga("./textures/weapons/smg/smg0.tga", 0);
	textures[21] = parse_tga("./textures/weapons/smg/smg1.tga", 0);
	textures[22] = parse_tga("./textures/weapons/smg/smg2.tga", 0);
	textures[23] = parse_tga("./textures/weapons/shotgun/shotgun0.tga", 0);
	textures[24] = parse_tga("./textures/weapons/shotgun/shotgun1.tga", 0);
	textures[25] = parse_tga("./textures/weapons/shotgun/shotgun2.tga", 0);
	textures[26] = parse_tga("./textures/weapons/revolver/revolver0.tga", 0);
	textures[27] = parse_tga("./textures/weapons/revolver/revolver1.tga", 0);
	textures[28] = parse_tga("./textures/weapons/revolver/revolver2.tga", 0);
	textures[29] = parse_tga("./textures/weapons/nyan_gun/nyan_gun0.tga", 0);
	textures[30] = parse_tga("./textures/weapons/nyan_gun/nyan_gun1.tga", 0);
	textures[31] = parse_tga("./textures/weapons/nyan_gun/nyan_gun2.tga", 0);
	textures[32] = parse_tga("./textures/weapons/grenade/grenade0.tga", 0);
	textures[33] = parse_tga("./textures/weapons/grenade/grenade1.tga", 0);
	textures[34] = parse_tga("./textures/weapons/claymore/claymore0.tga", 0);
	textures[35] = parse_tga("./textures/weapons/claymore/claymore1.tga", 0);
	textures[36] = parse_tga("./textures/hud/in_game_editor.tga", 1);
	textures[37] = parse_tga("./textures/environment/parking.tga", 0);
	game->ntextures = 38;
	return (textures);
}
