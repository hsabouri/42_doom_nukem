/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/05/15 12:00:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(void)
{
	t_game game;

	//a remettre a la fin pour charger toutes les textures au moment generation map
	game.textures = load_all_textures(&game);

	t_vec2 *points = (t_vec2 *)malloc(sizeof(t_vec2) * 20);
	points[0] = ((t_vec2){7, 6});
	points[1] = ((t_vec2){8, 7});
	points[2] = ((t_vec2){8, 11});
	points[3] = ((t_vec2){5, 12});
	points[4] = ((t_vec2){4, 12});
	points[5] = ((t_vec2){1, 11});
	points[6] = ((t_vec2){1, 7});
	points[7] = ((t_vec2){2, 6});
	points[8] = ((t_vec2){4, 6});
	points[9] = ((t_vec2){5, 6});
	points[10] = ((t_vec2){5, 4.5});
	points[11] = ((t_vec2){4, 4});
	points[12] = ((t_vec2){6, 2});
	points[13] = ((t_vec2){6.5, 3});
	points[14] = ((t_vec2){7, 3});
	points[15] = ((t_vec2){7, 2});
	points[16] = ((t_vec2){8, 0});
	points[17] = ((t_vec2){9, 0});
	points[18] = ((t_vec2){9, 5});
	points[19] = ((t_vec2){8, 5});

	t_weapon *gun = (t_weapon *)safe_malloc(sizeof(t_weapon) * 7, "generate_map");
	gun[0] = ((t_weapon) {
		(t_weapon_type) GUN,
		1,
		15,
		20,
		20,
		50,
		(t_shot_type) HITSCAN,
		-1,
		init_sprite_gun(game.textures),
		200
	});
	gun[1] = ((t_weapon) {
		(t_weapon_type) SMG,
		1,
		80,
		80,
		30,
		100,
		(t_shot_type) HITSCAN,
		-1,
		init_sprite_smg(game.textures),
		250
	});
	gun[2] = ((t_weapon) {
		(t_weapon_type) SHOTGUN,
		1,
		10,
		10,
		70,
		30,
		(t_shot_type) SHOTS,
		-1,
		init_sprite_shotgun(game.textures),
		20
	});
	gun[3] = ((t_weapon) {
		(t_weapon_type) REVOLVER,
		1,
		6,
		6,
		90,
		20,
		(t_shot_type) HITSCAN,
		-1,
		init_sprite_revolver(game.textures),
		250
	});
	gun[4] = ((t_weapon) {
		(t_weapon_type) NYAN_GUN,
		1,
		10,
		10,
		10000,
		30,
		(t_shot_type) SHOTS,
		-1,
		init_sprite_nyan_gun(game.textures),
		15
	});
	gun[5] = ((t_weapon) {
		(t_weapon_type) GRENADE,
		2,
		5,
		5,
		50,
		20,
		(t_shot_type) SHOTS,
		1,
		init_sprite_grenade(game.textures),
		200
	});
	gun[6] = ((t_weapon) {
		(t_weapon_type) MINE,
		2,
		5,
		5,
		50,
		20,
		(t_shot_type) STATIC,
		2,
		init_sprite_mine(game.textures),
		0
	});

	t_mat *materials = (t_mat *)malloc(16 * sizeof(t_mat));
	materials[0] = (t_mat) { // White tiles
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[1],
		TILING,
		WHITE,
		NULL
	};
	materials[1] = (t_mat) { // Dark grey brick
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		game.textures,
		TILING,
		WHITE,
		NULL
	};
	t_mat *bricks = &materials[1];

	materials[2] = (t_mat) { // White tiles
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[1],
		TILING,
		WHITE,
		NULL
	};
	t_mat *tiles = &materials[2];

	materials[3] = (t_mat) { // key_card
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[2],
		NO_TILING,
		WHITE,
		NULL
	};
	t_mat *key = &materials[3];

	materials[4] = (t_mat) { // Skybox
		fvec2_new(0, f_from_int(1300)),
		fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		NO_COLOR,
		&game.textures[3],
		SKYBOX,
		WHITE,
		NULL,
	};
	t_mat *skybox = &materials[4];

	materials[5] = (t_mat) { // Fence + skybox
		fvec2_new(0, f_from_int(1300)),
		fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		NO_COLOR,
		&game.textures[3],
		SKYBOX,
		WHITE,
		&materials[7]
	};
	t_mat *fence_skybox = &materials[5];

	materials[6] = (t_mat) { // Filtered wall
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		game.textures,
		TILING,
		RED,
		NULL
	};
	t_mat *filtered_wall = &materials[6];

	materials[7] = (t_mat) { // Fence
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[4],
		TILING,
		WHITE,
		NULL
	};
	t_mat *fence = &materials[7];

	materials[8] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[5],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[9] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[6],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[10] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[7],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[11] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[8],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[12] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[9],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[13] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[10],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[14] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[11],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[15] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&game.textures[12],
		NO_TILING,
		WHITE,
		NULL
	};

	t_array	*multi_mats = (t_array *)safe_malloc(sizeof(t_array) * 2, "init");
	multi_mats[0] = anew(NULL, 8, sizeof(t_mat *));

	t_mat	*yolo = &materials[8];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[9];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[10];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[11];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[12];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[13];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[14];
	apush(&multi_mats[0], &yolo);
	yolo = &materials[15];
	apush(&multi_mats[0], &yolo);

	multi_mats[1] = anew(NULL, 1, sizeof(t_mat *));
	apush(&multi_mats[1], &key);

	t_wall *walls = (t_wall *)malloc(29 * sizeof(t_wall));
	walls[0] =  ((t_wall){fvec2_new(0, 0), -1, 9, 0, bricks,(t_vec2){0, 2.5},(t_vec2){0, 2.5}});
	walls[1] =  ((t_wall){fvec2_new(0, 0), -1, 0, 1, bricks,(t_vec2){0, 2.5},(t_vec2){0, 2.5}});
	walls[2] =  ((t_wall){fvec2_new(0, 0), -1, 1, 2, filtered_wall,(t_vec2){0, 2.5},(t_vec2){0, 2.5}});
	walls[3] =  ((t_wall){fvec2_new(0, 0), -1, 2, 3, fence_skybox,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[4] =  ((t_wall){fvec2_new(0, 0), -1, 3, 4, fence_skybox,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[5] =  ((t_wall){fvec2_new(0, 0), -1, 4, 5, fence_skybox,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[6] =  ((t_wall){fvec2_new(0, 0), -1, 5, 6, bricks,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[7] =  ((t_wall){fvec2_new(0, 0), -1, 6, 7, bricks,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[8] =  ((t_wall){fvec2_new(0, 0), -1, 7, 8, bricks,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[9] =  ((t_wall){fvec2_new(0, 0), 0, 8, 9, bricks,(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[10] = ((t_wall){fvec2_new(0, 0), 0, 8, 9, bricks,(t_vec2){0.4,2.9},(t_vec2){0.4, 2.9}});
	walls[11] = ((t_wall){fvec2_new(0, 0), -1, 9, 10, bricks,(t_vec2){0.4,2.9},(t_vec2){0.4, 2.9}});
	walls[12] = ((t_wall){fvec2_new(0, 0), 1, 10, 11, bricks,(t_vec2){0.4,2.9},(t_vec2){0.4, 2.9}});
	walls[13] = ((t_wall){fvec2_new(0, 0), -1, 11, 8, bricks,(t_vec2){0.4,2.9},(t_vec2){0.4, 2.9}});
	walls[14] = ((t_wall){fvec2_new(0, 0), 1, 10, 11, bricks,(t_vec2){0.8, 3.3},(t_vec2){0.8, 3.3}});
	walls[15] = ((t_wall){fvec2_new(0, 0), -1, 11, 12, bricks,(t_vec2){0.8, 3.3},(t_vec2){0.8, 3.3}});
	walls[16] = ((t_wall){fvec2_new(0, 0), 2, 12, 13, bricks,(t_vec2){0.8, 3.3},(t_vec2){0.8, 3.3}});
	walls[17] = ((t_wall){fvec2_new(0, 0), -1, 13, 10, bricks,(t_vec2){0.8, 3.3},(t_vec2){0.8, 3.3}});
	walls[18] = ((t_wall){fvec2_new(0, 0), 2, 12, 13, bricks,(t_vec2){1.2, 3.7},(t_vec2){1.2, 3.7}});
	walls[19] = ((t_wall){fvec2_new(0, 0), -1, 13, 14, bricks,(t_vec2){1.2, 3.7},(t_vec2){1.2, 3.7}});
	walls[20] = ((t_wall){fvec2_new(0, 0), 3, 14, 15, bricks,(t_vec2){1.2, 3.7},(t_vec2){1.2, 3.7}});
	walls[21] = ((t_wall){fvec2_new(0, 0), -1, 15, 12, bricks,(t_vec2){1.2, 3.7},(t_vec2){1.2, 3.7}});
	walls[22] = ((t_wall){fvec2_new(0, 0), 3, 14, 15, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});
	walls[23] = ((t_wall){fvec2_new(0, 0), -1, 15, 16, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});
	walls[24] = ((t_wall){fvec2_new(0, 0), -1, 16, 17, bricks,(t_vec2){-30, 4.1},(t_vec2){-30, 4.1}});
	walls[25] = ((t_wall){fvec2_new(0, 0), -1, 17, 18, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});
	walls[26] = ((t_wall){fvec2_new(0, 0), -1, 18, 19, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});
	walls[27] = ((t_wall){fvec2_new(0, 0), -1, 19, 14, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});
	walls[28] = ((t_wall){fvec2_new(0, 0), -1, 19, 14, bricks,(t_vec2){-30, 4.1},(t_vec2){-30,  4.1}});

	t_portal *portals = (t_portal *)malloc(4 * sizeof(t_portal));
	portals[0] = ((t_portal){0, 1, 9, 10, 8, 9, fence, 0});
	portals[1] = ((t_portal){1, 2, 12, 14, 10, 11, NULL, 0});
	portals[2] = ((t_portal){2, 3, 16, 18, 12, 13, NULL, 0});
	portals[3] = ((t_portal){3, 4, 20, 22, 14, 15, NULL, 0});

	t_sector *sectors = (t_sector *)malloc(5 * sizeof(t_sector));
	sectors[0] = ((t_sector){0, 10, 0, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 2.50}, (t_color) {125, 125, 125, 255},
	tiles, tiles, fvec2_new(0, 0), (t_vec2){0, 0},0});
	sectors[1] = ((t_sector){10, 4, 1, (t_vec3){0, 0, 0.4}, (t_vec3){0, 0, 2.9}, WHITE, tiles, tiles, fvec2_new(0, 0), (t_vec2){0, 0},1});
	sectors[2] = ((t_sector){14, 4, 2, (t_vec3){0, 0, 0.8}, (t_vec3){0, 0, 3.3}, WHITE, tiles, tiles, fvec2_new(0, 0), (t_vec2){0, 0},0});
	sectors[3] = ((t_sector){18, 4, 3, (t_vec3){0, 0, 1.2}, (t_vec3){0, 0, 3.7}, WHITE, tiles, tiles, fvec2_new(0, 0), (t_vec2){0, 0},1});
	sectors[4] = ((t_sector){22, 6, 4, (t_vec3){0, 0, -30}, (t_vec3){0, 0, 4.1}, WHITE, tiles, tiles, fvec2_new(0, 0), (t_vec2){0, 0},0});
	
	t_entity *entities = (t_entity *)malloc(4 * sizeof(t_entity));
	entities[0] = ((t_entity){
		0,
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){6, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){6, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		&multi_mats[0],
		0
	});
	entities[1] = ((t_entity){
		1,
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){6, 8, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){6, 8, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		&multi_mats[0],
		1
	});
	entities[2] = ((t_entity){
		2,
		(t_ph) {
			0.02,
			1.50,
			0.5,
			2,
			(t_vec3){5, 8.5, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0.02,
			1.50,
			0.5,
			2,
			(t_vec3){5, 8.5, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		&multi_mats[0],
		1
	});
	entities[3] = ((t_entity){
		3,
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){5, 8.5, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0.02,
			1.50,
			0.5,
			3,
			(t_vec3){5, 8.5, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		&multi_mats[1],
		1
	});

	t_array inventory = safe_anew(NULL, 1, sizeof(t_entity *), "generate_map");
	t_entity *ent = &entities[3];
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);
	apush(&inventory, &ent);

	t_player player = (t_player) {
		(t_entity) {
			-1,
			(t_ph) {
				0.02,
				1.50,
				0.5,
				0,
				(t_vec3){2, 10, 0},
				(t_vec3){0, 0, 0},
				(t_vec3){1, 1, 1},
				0,
				0,
				0,
				0,
				0
			},
			(t_ph) {
				0.02,
				1.50,
				0.5,
				0,
				(t_vec3){2, 10, 0},
				(t_vec3){0, 0, 0},
				(t_vec3){1, 1, 1},
				0,
				0,
				0,
				0,
				0
			},
			&multi_mats[0],
			1
		},
		90,
		{0, 1},
		6,
		0,
		inventory
	};

	//pabesoindelesauvgardé
	// t_entity dummy = ((t_entity){
	// 	10,
	// 	(t_ph) {
	// 		0,
	// 		0,
	// 		0,
	// 		0,
	// 		(t_vec3){0, 0, 0},
	// 		(t_vec3){0, 0, 0},
	// 		(t_vec3){0, 0, 0},
	// 		0,
	// 		0,
	// 		2,
	// 		0,
	// 		0
	// 	},
	// 	(t_ph) {
	// 		0,
	// 		0,
	// 		0,
	// 		0,
	// 		(t_vec3){0, 0, 0},
	// 		(t_vec3){0, 0, 0},
	// 		(t_vec3){0, 0, 0},
	// 		0,
	// 		0,
	// 		2,
	// 		0,
	// 		0
	// 	},
	// 	multi,
	// 	0
	// 	});

	t_array c_log = anew(NULL, 100, sizeof(t_trigger));

	t_game_event * first_e = (t_game_event *)malloc(sizeof(t_game_event));

	*first_e = (t_game_event){
		(t_pelem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_INTERACT, entities[2] // Game event : list event wanted
			}
		};

	t_game_event * secon_e = (t_game_event *)malloc(sizeof(t_game_event));
	*secon_e = (t_game_event){
		(t_pelem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_TOUCH, entities[1] // Game event : list event wanted
			}
		};

	t_game_event * third_e = (t_game_event *)malloc(sizeof(t_game_event));
	*third_e = (t_game_event){
		(t_pelem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_SEE, entities[0] // Game event : list event wanted
			}
		};

	// 		t_game_event * kuadro_e = (t_game_event *)malloc(sizeof(t_game_event));
	// *kuadro_e = (t_game_event){
	// 	(t_pelem) {NULL},
	// 	(t_trigger){
	// 		dummy, TRIGGER_SECTOR, dummy // Game event : list event wanted
	// 		}
		// };

	t_plist	g_e	= lpnew((t_pelem *)first_e);
	lppush(&g_e, (t_pelem *)secon_e);
	lppush(&g_e, (t_pelem *)third_e);
	// lppush(&g_e, kuadro_e);

	game.player = player;
	game.log = c_log;
	game.waiting_events = g_e;
	game.entities = entities;
	game.nentities = 4;
	game.sectors = sectors;
	game.nsectors = 5;
	game.walls = walls;
	game.nwalls = 29;
	game.nuwalls = 0;
	game.portals = portals;
	game.nportals = 4;
	game.points = points;
	game.npoints = 20;
	game.materials = materials;
	game.nmaterials = 16;
	game.multi_mats = multi_mats;
	game.nmulti_mats = 2;
	game.weapons = gun;
	game.nweapons = 7;
	game.played_music = 0;
	return (game);
}
