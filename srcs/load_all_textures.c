/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:07:49 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/12 12:19:10 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_img	*load_all_textures_5(t_img *textures)
{
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
	return (load_all_textures_6(textures));
}

static t_img	*load_all_textures_4(t_img *textures)
{
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
	return (load_all_textures_5(textures));
}

static t_img	*load_all_textures_3(t_img *t)
{
	t[44] = parse_tga("./textures/ennemies/smg_marine/smg_marine6.tga", 0);
	t[45] = parse_tga("./textures/ennemies/smg_marine/smg_marine7.tga", 0);
	t[46] = parse_tga("./textures/ennemies/raclure/raclure0.tga", 0);
	t[47] = parse_tga("./textures/ennemies/raclure/raclure1.tga", 0);
	t[48] = parse_tga("./textures/ennemies/raclure/raclure2.tga", 0);
	t[49] = parse_tga("./textures/ennemies/raclure/raclure3.tga", 0);
	t[50] = parse_tga("./textures/ennemies/raclure/raclure4.tga", 0);
	t[51] = parse_tga("./textures/ennemies/raclure/raclure5.tga", 0);
	t[52] = parse_tga("./textures/ennemies/raclure/raclure6.tga", 0);
	t[53] = parse_tga("./textures/ennemies/raclure/raclure7.tga", 0);
	t[54] = parse_tga("./textures/ennemies/red_marine/red_marine0.tga", 0);
	t[55] = parse_tga("./textures/ennemies/red_marine/red_marine1.tga", 0);
	t[56] = parse_tga("./textures/ennemies/red_marine/red_marine2.tga", 0);
	t[57] = parse_tga("./textures/ennemies/red_marine/red_marine3.tga", 0);
	t[58] = parse_tga("./textures/ennemies/red_marine/red_marine4.tga", 0);
	t[59] = parse_tga("./textures/ennemies/red_marine/red_marine5.tga", 0);
	t[60] = parse_tga("./textures/ennemies/red_marine/red_marine6.tga", 0);
	t[61] = parse_tga("./textures/ennemies/red_marine/red_marine7.tga", 0);
	t[62] = parse_tga("./textures/items/key_card_blue.tga", 0);
	t[63] = parse_tga("./textures/items/key_card_red.tga", 0);
	t[64] = parse_tga("./textures/items/key_card_purple.tga", 0);
	t[65] = parse_tga("./textures/items/apple.tga", 0);
	t[66] = parse_tga("./textures/items/fish.tga", 0);
	t[67] = parse_tga("./textures/items/meat.tga", 0);
	return (load_all_textures_4(t));
}

static t_img	*load_all_textures_2(t_img *t)
{
	t[20] = parse_tga("./textures/weapons/smg/smg0.tga", 0);
	t[21] = parse_tga("./textures/weapons/smg/smg1.tga", 0);
	t[22] = parse_tga("./textures/weapons/smg/smg2.tga", 0);
	t[23] = parse_tga("./textures/weapons/shotgun/shotgun0.tga", 0);
	t[24] = parse_tga("./textures/weapons/shotgun/shotgun1.tga", 0);
	t[25] = parse_tga("./textures/weapons/shotgun/shotgun2.tga", 0);
	t[26] = parse_tga("./textures/weapons/revolver/revolver0.tga", 0);
	t[27] = parse_tga("./textures/weapons/revolver/revolver1.tga", 0);
	t[28] = parse_tga("./textures/weapons/revolver/revolver2.tga", 0);
	t[29] = parse_tga("./textures/weapons/nyan_gun/nyan_gun0.tga", 0);
	t[30] = parse_tga("./textures/weapons/nyan_gun/nyan_gun1.tga", 0);
	t[31] = parse_tga("./textures/weapons/nyan_gun/nyan_gun2.tga", 0);
	t[32] = parse_tga("./textures/items/ammo_secondary.tga", 0);
	t[33] = parse_tga("./textures/environment/lavabo.tga", 1);
	t[34] = parse_tga("./textures/environment/lavabo_2.tga", 1);
	t[35] = parse_tga("./textures/environment/door.tga", 0);
	t[36] = parse_tga("./textures/hud/in_game_editor.tga", 1);
	t[37] = parse_tga("./textures/environment/parking.tga", 0);
	t[38] = parse_tga("./textures/ennemies/smg_marine/smg_marine0.tga", 0);
	t[39] = parse_tga("./textures/ennemies/smg_marine/smg_marine1.tga", 0);
	t[40] = parse_tga("./textures/ennemies/smg_marine/smg_marine2.tga", 0);
	t[41] = parse_tga("./textures/ennemies/smg_marine/smg_marine3.tga", 0);
	t[42] = parse_tga("./textures/ennemies/smg_marine/smg_marine4.tga", 0);
	t[43] = parse_tga("./textures/ennemies/smg_marine/smg_marine5.tga", 0);
	return (load_all_textures_3(t));
}

t_img			*load_all_textures(t_game *game)
{
	t_img	*t;

	game->ntextures = 133;
	t = (t_img *)safe_malloc(game->ntextures * sizeof(t_img), "textures");
	t[0] = parse_tga("./textures/environment/wall.tga", 1);
	t[1] = parse_tga("./textures/environment/amordret_pic.tga", 1);
	t[2] = parse_tga("./textures/items/key_card_green.tga", 0);
	t[3] = parse_tga("./textures/environment/skybox.tga", 1);
	t[4] = parse_tga("./textures/environment/fence.tga", 1);
	t[5] = parse_tga("./textures/ennemies/gun_marine/gun_marine0.tga", 0);
	t[6] = parse_tga("./textures/ennemies/gun_marine/gun_marine1.tga", 0);
	t[7] = parse_tga("./textures/ennemies/gun_marine/gun_marine2.tga", 0);
	t[8] = parse_tga("./textures/ennemies/gun_marine/gun_marine3.tga", 0);
	t[9] = parse_tga("./textures/ennemies/gun_marine/gun_marine4.tga", 0);
	t[10] = parse_tga("./textures/ennemies/gun_marine/gun_marine5.tga", 0);
	t[11] = parse_tga("./textures/ennemies/gun_marine/gun_marine6.tga", 0);
	t[12] = parse_tga("./textures/ennemies/gun_marine/gun_marine7.tga", 0);
	t[13] = parse_tga("./textures/hud/cross.tga", 0);
	t[14] = parse_tga("./textures/hud/full_life.tga", 0);
	t[15] = parse_tga("./textures/hud/empty_life.tga", 0);
	t[16] = parse_tga("./textures/hud/help.tga", 0);
	t[17] = parse_tga("./textures/weapons/gun/gun0.tga", 0);
	t[18] = parse_tga("./textures/weapons/gun/gun1.tga", 0);
	t[19] = parse_tga("./textures/weapons/gun/gun2.tga", 0);
	return (load_all_textures_2(t));
}
