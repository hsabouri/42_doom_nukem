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
	materials[11] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[11], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL
	};
	materials[12] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[12], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[13] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[2], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	return (materials);
}

static t_mat	*init_mat_3(t_mat *materials, t_game *game)
{
	materials[7] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[7], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[8] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[8], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[9] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[9], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[10] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[10], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	return (materials);
}

static t_mat	*init_mat_2(t_mat *materials, t_game *game)
{
	materials[3] = (t_mat) {
		.pos = fvec2_new(0, f_from_int(1300)),
		.sca = fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		.color = NO_COLOR, .texture = &game->textures[3], .mode = SKYBOX,
		.filter = WHITE, .overlay = &materials[4]
	};
	materials[4] = (t_mat) {
		.pos = fvec2_new(0, 0),	.sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[4], .mode = TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[5] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[5], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[6] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[6], .mode = NO_TILING,
		.filter = WHITE, .overlay = NULL
	};
	return (materials);
}

static t_mat	*init_mats(t_game *game)
{
	t_mat *materials;

	materials = (t_mat *)safe_malloc(14 * sizeof(t_mat), "generate_map");
	materials[0] = (t_mat) {
		.pos = fvec2_new(0, 0),	.sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = game->textures, .mode = TILING,
		.filter = WHITE, .overlay = NULL
	};
	materials[1] = (t_mat) {
		.pos = fvec2_new(0, 0), .sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[1], .mode = TILING,
		.filter = WHITE, .overlay = NULL
		};
	materials[2] = (t_mat) {
		.pos = fvec2_new(0, f_from_int(1300)),
		.sca = fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		.color = NO_COLOR, .texture = &game->textures[3], .mode = SKYBOX,
		.filter = WHITE, .overlay = NULL
	};
	materials = init_mat_2(materials, game);
	materials = init_mat_3(materials, game);
	materials = init_mat_4(materials, game);
	game->nmaterials = 14;
	return (materials);
}

t_game	generate_map(void)
{
	t_game		game;

	game.textures = load_all_textures(&game);
	game.materials = init_mats(&game);
	printf("buh\n");
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
