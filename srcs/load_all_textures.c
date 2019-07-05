/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:07:49 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/23 16:02:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_img	*load_all_textures(t_game *game)
{
	t_img	*textures;

	game->ntextures = 119;
	textures = (t_img *)safe_malloc(game->ntextures * sizeof(t_img), "textures");
	textures[0] = parse_tga("./textures/wall.tga", 1);
	textures[1] = parse_tga("./textures/floor.tga", 1);
	textures[2] = parse_tga("./textures/items/key_card_green.tga", 0);
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
	textures[32] = parse_tga("./textures/items/ammo_secondary.tga", 0);
	textures[33] = parse_tga("./textures/environment/lavabo.tga", 1);
	textures[34] = parse_tga("./textures/environment/lavabo_2.tga", 1);
	textures[35] = parse_tga("./textures/environment/door.tga", 0);
	textures[36] = parse_tga("./textures/hud/in_game_editor.tga", 1);
	textures[37] = parse_tga("./textures/environment/parking.tga", 0);
	textures[38] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine0.tga", 0);
	textures[39] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine1.tga", 0);
	textures[40] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine2.tga", 0);
	textures[41] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine3.tga", 0);
	textures[42] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine4.tga", 0);
	textures[43] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine5.tga", 0);
	textures[44] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine6.tga", 0);
	textures[45] = parse_tga("./textures/multi_sprite/smg_marine/smg_marine7.tga", 0);
	textures[46] = parse_tga("./textures/multi_sprite/black_marine/black_marine0.tga", 0);
	textures[47] = parse_tga("./textures/multi_sprite/black_marine/black_marine1.tga", 0);
	textures[48] = parse_tga("./textures/multi_sprite/black_marine/black_marine2.tga", 0);
	textures[49] = parse_tga("./textures/multi_sprite/black_marine/black_marine3.tga", 0);
	textures[50] = parse_tga("./textures/multi_sprite/black_marine/black_marine4.tga", 0);
	textures[51] = parse_tga("./textures/multi_sprite/black_marine/black_marine5.tga", 0);
	textures[52] = parse_tga("./textures/multi_sprite/black_marine/black_marine6.tga", 0);
	textures[53] = parse_tga("./textures/multi_sprite/black_marine/black_marine7.tga", 0);
	textures[54] = parse_tga("./textures/multi_sprite/red_marine/red_marine0.tga", 0);
	textures[55] = parse_tga("./textures/multi_sprite/red_marine/red_marine1.tga", 0);
	textures[56] = parse_tga("./textures/multi_sprite/red_marine/red_marine2.tga", 0);
	textures[57] = parse_tga("./textures/multi_sprite/red_marine/red_marine3.tga", 0);
	textures[58] = parse_tga("./textures/multi_sprite/red_marine/red_marine4.tga", 0);
	textures[59] = parse_tga("./textures/multi_sprite/red_marine/red_marine5.tga", 0);
	textures[60] = parse_tga("./textures/multi_sprite/red_marine/red_marine6.tga", 0);
	textures[61] = parse_tga("./textures/multi_sprite/red_marine/red_marine7.tga", 0);
	textures[62] = parse_tga("./textures/items/key_card_blue.tga", 0);
	textures[63] = parse_tga("./textures/items/key_card_red.tga", 0);
	textures[64] = parse_tga("./textures/items/key_card_purple.tga", 0);
	textures[65] = parse_tga("./textures/items/apple.tga", 0);
	textures[66] = parse_tga("./textures/items/fish.tga", 0);
	textures[67] = parse_tga("./textures/items/meat.tga", 0);
	textures[68] = parse_tga("./textures/items/medipack.tga", 0);
	textures[69] = parse_tga("./textures/items/ammo.tga", 0);
	textures[70] = parse_tga("./textures/items/close_door_red.tga", 0);
	textures[71] = parse_tga("./textures/items/close_door_blue.tga", 0);
	textures[72] = parse_tga("./textures/items/close_door_green.tga", 0);
	textures[73] = parse_tga("./textures/items/close_door_purple.tga", 0);
	textures[74] = parse_tga("./textures/items/open_door_red.tga", 0);
	textures[75] = parse_tga("./textures/items/open_door_blue.tga", 0);
	textures[76] = parse_tga("./textures/items/open_door_green.tga", 0);
	textures[77] = parse_tga("./textures/items/open_door_purple.tga", 0);
	textures[78] = parse_tga("./textures/items/lamp.tga", 0);
	textures[79] = parse_tga("./textures/items/ceil_lamp.tga", 0);
	textures[80] = parse_tga("./textures/items/plant_1.tga", 0);
	textures[81] = parse_tga("./textures/items/plant_2_0.tga", 0);
	textures[82] = parse_tga("./textures/items/plant_2_1.tga", 0);
	textures[83] = parse_tga("./textures/items/plant_3.tga", 0);
	textures[84] = parse_tga("./textures/items/plant_4.tga", 0);
	textures[85] = parse_tga("./textures/items/trash_1.tga", 0);
	textures[86] = parse_tga("./textures/items/trash_2.tga", 0);
	textures[87] = parse_tga("./textures/environment/amordret.tga", 1);
	textures[88] = parse_tga("./textures/environment/boite.tga", 1);
	textures[89] = parse_tga("./textures/environment/building.tga", 1);
	textures[90] = parse_tga("./textures/environment/casier.tga", 1);
	textures[91] = parse_tga("./textures/environment/cross.tga", 1);
	textures[92] = parse_tga("./textures/environment/fenetre_grillage.tga", 1);
	textures[93] = parse_tga("./textures/environment/floor_accueil.tga", 1);
	textures[94] = parse_tga("./textures/environment/fmerding.tga", 1);
	textures[95] = parse_tga("./textures/environment/hsabouri.tga", 1);
	textures[96] = parse_tga("./textures/environment/lbougero.tga", 1);
	textures[97] = parse_tga("./textures/environment/iporsenn.tga", 1);
	textures[98] = parse_tga("./textures/environment/library.tga", 1);
	textures[99] = parse_tga("./textures/environment/moquette.tga", 1);
	textures[100] = parse_tga("./textures/environment/mur_entrepot.tga", 1);
	textures[101] = parse_tga("./textures/environment/mur_wc.tga", 1);
	textures[102] = parse_tga("./textures/environment/nope_grumpy.tga", 1);
	textures[103] = parse_tga("./textures/environment/road_1.tga", 1);
	textures[104] = parse_tga("./textures/environment/road_2.tga", 1);
	textures[105] = parse_tga("./textures/environment/sofa.tga", 1);
	textures[106] = parse_tga("./textures/environment/sol_entrepot.tga", 1);
	textures[107] = parse_tga("./textures/environment/sol_wc.tga", 1);
	textures[108] = parse_tga("./textures/environment/street.tga", 1);
	textures[109] = parse_tga("./textures/environment/wall_accueil.tga", 1);
	textures[110] = parse_tga("./textures/environment/window.tga", 1);
	textures[111] = parse_tga("./textures/environment/wood.tga", 1);
	textures[112] = parse_tga("./textures/environment/wood_2.tga", 1);
	textures[113] = parse_tga("./textures/environment/ceil.tga", 1);
	textures[114] = parse_tga("./textures/environment/desk.tga", 1);
	textures[115] = parse_tga("./textures/environment/stairs_up.tga", 1);
	textures[116] = parse_tga("./textures/environment/stairs_down.tga", 1);
	textures[117] = parse_tga("./textures/environment/stairs_up_down.tga", 1);
	textures[118] = parse_tga("./textures/environment/wc.tga", 1);
	return (textures);
}
