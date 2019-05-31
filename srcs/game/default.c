/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/05/22 14:08:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_mat	*init_mat_4(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(3), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[43], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
		tmp.texture = &game->textures[44];
	materials[19] = tmp;
	tmp.texture = &game->textures[44];
	materials[20] = tmp;
	tmp.texture = &game->textures[45];
	materials[21] = tmp;
	tmp.texture = &game->textures[46];
	materials[22] = tmp;
	tmp.texture = &game->textures[47];
	materials[23] = tmp;
	tmp.texture = &game->textures[48];
	materials[24] = tmp;
	tmp.texture = &game->textures[49];
	materials[25] = tmp;
	tmp.texture = &game->textures[50];
	materials[26] = tmp;
	return (materials);
}

static t_mat	*init_mat_3(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(3), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[10], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
	materials[10] = tmp;
	tmp.texture = &game->textures[11];
	materials[11] = tmp;
	tmp.texture = &game->textures[12];
	materials[12] = tmp;
	tmp.texture = &game->textures[2];
	materials[13] = tmp;
	tmp.texture = &game->textures[38];
	materials[14] = tmp;
	tmp.texture = &game->textures[39];
	materials[15] = tmp;
	tmp.texture = &game->textures[40];
	materials[16] = tmp;
	tmp.texture = &game->textures[41];
	materials[17] = tmp;
	tmp.texture = &game->textures[42];
	materials[18] = tmp;
	return (materials);
}

static t_mat	*init_mat_2(t_mat *materials, t_game *game)
{
	t_mat tmp;

	materials[3] = (t_mat) {.pos = fvec2_new(0, f_from_int(1300)),
		.sca = fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		.color = NO_COLOR, .texture = &game->textures[3], .mode = SKYBOX,
		.filter = WHITE, .overlay = &materials[4]};
	materials[4] = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[4], .mode = TILING,
		.filter = WHITE, .overlay = NULL};
	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(3), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[5], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL};
	materials[5] = tmp;
	tmp.sca.u = f_from_int(2);
	tmp.texture = &game->textures[6];
	materials[6] = tmp;
	tmp.texture = &game->textures[7];
	materials[7] = tmp;
	tmp.texture = &game->textures[8];
	materials[8] = tmp;
	tmp.texture = &game->textures[9];
	materials[9] = tmp;
	return (materials);
}

static t_mat	*init_mats(t_game *game)
{
	t_mat	*materials;
	t_mat	tmp;

	materials = (t_mat *)safe_malloc(46 * sizeof(t_mat), "generate_map");
	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = game->textures, .mode = TILING,
		.filter = WHITE, .overlay = NULL};
	materials[0] = tmp;
	tmp.texture = &game->textures[1];
	materials[1] = tmp;
	materials[2] = (t_mat) {.pos = fvec2_new(0, f_from_int(1300)),
		.sca = fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		.color = NO_COLOR, .texture = &game->textures[3], .mode = SKYBOX,
		.filter = WHITE, .overlay = NULL};
	materials = init_mat_2(materials, game);
	materials = init_mat_3(materials, game);
	materials = init_mat_4(materials, game);
	materials = init_mat_5(materials, game);
	materials = init_mat_6(materials, game);
	materials = init_mat_7(materials, game);
	game->nmaterials = 46;
	return (materials);
}

t_game	generate_map(void)
{
	t_game		game;

	game.textures = load_all_textures(&game);
	game.materials = init_mats(&game);
	game.multi_mats = init_multi_sprite(&game, game.materials);
	game.points = init_points(&game);
	game.walls = init_walls(&game);
	game.portals = (t_portal *)safe_malloc(0 * sizeof(t_portal), "generate_map");
	game.nportals = 0;
	game.sectors = init_sector(&game);
	game.classes = init_classe(&game, game.multi_mats);
	game.player = player_default(game);
	game.entities = init_entities(&game);

	t_array c_log = anew(NULL, 100, sizeof(t_trigger));
	t_game_event * first_e = (t_game_event *)malloc(sizeof(t_game_event));
	*first_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game.player.my_entity, TRIGGER_INTERACT, game.entities[2] // Game event : list event wanted
			}
		};
	t_game_event * secon_e = (t_game_event *)malloc(sizeof(t_game_event));
	*secon_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game.player.my_entity, TRIGGER_TOUCH, game.entities[1] // Game event : list event wanted
			}
		};
	t_game_event * third_e = (t_game_event *)malloc(sizeof(t_game_event));
	*third_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game.player.my_entity, TRIGGER_SEE, game.entities[0] // Game event : list event wanted
			}
		};

	t_plist	g_e	= lpnew((t_pelem *)first_e);
	lppush(&g_e, (t_pelem *)secon_e);
	lppush(&g_e, (t_pelem *)third_e);
	
	game.log = c_log;
	game.waiting_events = g_e;
	game.unique_e_id = 4;
	game.played_music = 0;
	return (game);
}
