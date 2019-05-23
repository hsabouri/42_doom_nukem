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
	textures[0] = parse_tga("./textures/wall.tga");
	textures[1] = parse_tga("./textures/floor.tga");
	textures[2] = parse_tga("./textures/items/key_card.tga");
	textures[3] = parse_tga("./textures/skybox.tga");
	textures[4] = parse_tga("./textures/fence.tga");
	textures[5] = parse_tga("./textures/multi_sprite/1.tga");
	textures[6] = parse_tga("./textures/multi_sprite/2.tga");
	textures[7] = parse_tga("./textures/multi_sprite/3.tga");
	textures[8] = parse_tga("./textures/multi_sprite/4.tga");
	textures[9] = parse_tga("./textures/multi_sprite/5.tga");
	textures[10] = parse_tga("./textures/multi_sprite/6.tga");
	textures[11] = parse_tga("./textures/multi_sprite/7.tga");
	textures[12] = parse_tga("./textures/multi_sprite/8.tga");
	textures[13] = parse_tga("./textures/hud/cross.tga");
	textures[14] = parse_tga("./textures/hud/full_life.tga");
	textures[15] = parse_tga("./textures/hud/empty_life.tga");
	textures[16] = parse_tga("./textures/hud/help.tga");
	textures[17] = parse_tga("./textures/weapons/gun/gun0.tga");
	textures[18] = parse_tga("./textures/weapons/gun/gun1.tga");
	textures[19] = parse_tga("./textures/weapons/gun/gun2.tga");
	textures[20] = parse_tga("./textures/weapons/smg/smg0.tga");
	textures[21] = parse_tga("./textures/weapons/smg/smg1.tga");
	textures[22] = parse_tga("./textures/weapons/smg/smg2.tga");
	textures[23] = parse_tga("./textures/weapons/shotgun/shotgun0.tga");
	textures[24] = parse_tga("./textures/weapons/shotgun/shotgun1.tga");
	textures[25] = parse_tga("./textures/weapons/shotgun/shotgun2.tga");
	textures[26] = parse_tga("./textures/weapons/revolver/revolver0.tga");
	textures[27] = parse_tga("./textures/weapons/revolver/revolver1.tga");
	textures[28] = parse_tga("./textures/weapons/revolver/revolver2.tga");
	textures[29] = parse_tga("./textures/weapons/nyan_gun/nyan_gun0.tga");
	textures[30] = parse_tga("./textures/weapons/nyan_gun/nyan_gun1.tga");
	textures[31] = parse_tga("./textures/weapons/nyan_gun/nyan_gun2.tga");
	textures[32] = parse_tga("./textures/weapons/grenade/grenade0.tga");
	textures[33] = parse_tga("./textures/weapons/grenade/grenade1.tga");
	textures[34] = parse_tga("./textures/weapons/claymore/claymore0.tga");
	textures[35] = parse_tga("./textures/weapons/claymore/claymore1.tga");
	textures[36] = parse_tga("./textures/hud/in_game_editor.tga");
	textures[37] = parse_tga("./textures/environment/parking.tga");
	game->ntextures = 38;
	return (textures);
}
