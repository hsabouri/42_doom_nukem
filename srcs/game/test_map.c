/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/04/26 12:23:28 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(void)
{
	t_game game;
	
	t_img *textures = (t_img *)safe_malloc(50 * sizeof(t_img), "textures");
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
	textures[20] = parse_tga("./textures/weapons/gun/gun3.tga");
	textures[21] = parse_tga("./textures/weapons/gun/gun4.tga");
	textures[22] = parse_tga("./textures/weapons/gun/gun5.tga");
	textures[23] = parse_tga("./textures/weapons/smg/smg0.tga");
	textures[24] = parse_tga("./textures/weapons/smg/smg1.tga");
	textures[25] = parse_tga("./textures/weapons/smg/smg2.tga");
	textures[26] = parse_tga("./textures/weapons/smg/smg3.tga");
	textures[27] = parse_tga("./textures/weapons/shotgun/shotgun0.tga");
	textures[28] = parse_tga("./textures/weapons/shotgun/shotgun1.tga");
	textures[29] = parse_tga("./textures/weapons/shotgun/shotgun2.tga");
	textures[30] = parse_tga("./textures/weapons/shotgun/shotgun3.tga");
	textures[31] = parse_tga("./textures/weapons/shotgun/shotgun4.tga");
	textures[32] = parse_tga("./textures/weapons/shotgun/shotgun5.tga");
	textures[33] = parse_tga("./textures/weapons/shotgun/shotgun6.tga");
	textures[34] = parse_tga("./textures/weapons/shotgun/shotgun7.tga");
	textures[35] = parse_tga("./textures/weapons/revolver/revolver0.tga");
	textures[36] = parse_tga("./textures/weapons/revolver/revolver1.tga");
	textures[37] = parse_tga("./textures/weapons/revolver/revolver2.tga");
	textures[38] = parse_tga("./textures/weapons/revolver/revolver3.tga");
	textures[39] = parse_tga("./textures/weapons/revolver/revolver4.tga");
	textures[40] = parse_tga("./textures/weapons/revolver/revolver5.tga");
	textures[41] = parse_tga("./textures/weapons/nyan_gun/nyan_gun0.tga");
	textures[42] = parse_tga("./textures/weapons/nyan_gun/nyan_gun1.tga");
	textures[43] = parse_tga("./textures/weapons/nyan_gun/nyan_gun2.tga");
	textures[44] = parse_tga("./textures/weapons/nyan_gun/nyan_gun3.tga");
	textures[45] = parse_tga("./textures/weapons/nyan_gun/nyan_gun4.tga");
	textures[46] = parse_tga("./textures/weapons/grenade/grenade0.tga");
	textures[47] = parse_tga("./textures/weapons/grenade/grenade1.tga");
	textures[48] = parse_tga("./textures/weapons/claymore/claymore0.tga");
	textures[49] = parse_tga("./textures/weapons/claymore/claymore1.tga");

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
		init_sprite_gun(textures),
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
		init_sprite_smg(textures),
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
		init_sprite_shotgun(textures),
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
		init_sprite_revolver(textures),
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
		init_sprite_nyan_gun(textures),
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
		init_sprite_grenade(textures),
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
		init_sprite_mine(textures),
		0
	});

	t_mat *materials = (t_mat *)malloc(16 * sizeof(t_mat));
	materials[0] = (t_mat) { // White tiles
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[1],
		TILING,
		WHITE,
		NULL
	};
	materials[1] = (t_mat) { // Dark grey brick
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		textures,
		TILING,
		WHITE,
		NULL
	};
	t_mat *bricks = &materials[1];

	materials[2] = (t_mat) { // White tiles
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[1],
		TILING,
		WHITE,
		NULL
	};
	t_mat *tiles = &materials[2];

	materials[3] = (t_mat) { // key_card
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[2],
		NO_TILING,
		WHITE,
		NULL
	};
	t_mat *key = &materials[3];

	materials[4] = (t_mat) { // Skybox
		fvec2_new(0, f_from_int(1300)),
		fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		NO_COLOR,
		&textures[3],
		SKYBOX,
		WHITE,
		NULL,
	};
	t_mat *skybox = &materials[4];

	materials[5] = (t_mat) { // Fence + skybox
		fvec2_new(0, f_from_int(1300)),
		fvec2_new(f_from_float(0.7), f_from_float(0.7)),
		NO_COLOR,
		&textures[3],
		SKYBOX,
		WHITE,
		&materials[7]
	};
	t_mat *fence_skybox = &materials[5];
	
	materials[6] = (t_mat) { // Filtered wall
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		textures,
		TILING,
		RED,
		NULL
	};
	t_mat *filtered_wall = &materials[6];

	materials[7] = (t_mat) { // Fence
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[4],
		TILING,
		WHITE,
		NULL
	};
	t_mat *fence = &materials[7];

	materials[8] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[5],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[9] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[6],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[10] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[7],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[11] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[8],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[12] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[9],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[13] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[10],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[14] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[11],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[15] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[12],
		NO_TILING,
		WHITE,
		NULL
	};

	t_array	multi = anew(NULL, 8, sizeof(t_mat *));
	t_mat	*yolo = &materials[8];
	apush(&multi, &yolo);
	yolo = &materials[9];
	apush(&multi, &yolo);
	yolo = &materials[10];
	apush(&multi, &yolo);
	yolo = &materials[11];
	apush(&multi, &yolo);
	yolo = &materials[12];
	apush(&multi, &yolo);
	yolo = &materials[13];
	apush(&multi, &yolo);
	yolo = &materials[14];
	apush(&multi, &yolo);
	yolo = &materials[15];
	apush(&multi, &yolo);

	t_array key_card = anew(NULL, 1, sizeof(t_mat *));
	apush(&key_card, &key);

	t_wall *walls = (t_wall *)malloc(29 * sizeof(t_wall));
	walls[0] =  ((t_wall){fvec2_new(0, 0), -1, 9, 0, bricks});
	walls[1] =  ((t_wall){fvec2_new(0, 0), -1, 0, 1, bricks});
	walls[2] =  ((t_wall){fvec2_new(0, 0), -1, 1, 2, filtered_wall});
	walls[3] =  ((t_wall){fvec2_new(0, 0), -1, 2, 3, fence_skybox});
	walls[4] =  ((t_wall){fvec2_new(0, 0), -1, 3, 4, fence_skybox});
	walls[5] =  ((t_wall){fvec2_new(0, 0), -1, 4, 5, fence_skybox});
	walls[6] =  ((t_wall){fvec2_new(0, 0), -1, 5, 6, bricks});
	walls[7] =  ((t_wall){fvec2_new(0, 0), -1, 6, 7, bricks});
	walls[8] =  ((t_wall){fvec2_new(0, 0), -1, 7, 8, bricks});
	walls[9] =  ((t_wall){fvec2_new(0, 0), 0, 8, 9, bricks});
	walls[10] = ((t_wall){fvec2_new(0, 0), 0, 8, 9, bricks});
	walls[11] = ((t_wall){fvec2_new(0, 0), -1, 9, 10, bricks});
	walls[12] = ((t_wall){fvec2_new(0, 0), 1, 10, 11, bricks});
	walls[13] = ((t_wall){fvec2_new(0, 0), -1, 11, 8, bricks});
	walls[14] = ((t_wall){fvec2_new(0, 0), 1, 10, 11, bricks});
	walls[15] = ((t_wall){fvec2_new(0, 0), -1, 11, 12, bricks});
	walls[16] = ((t_wall){fvec2_new(0, 0), 2, 12, 13, bricks});
	walls[17] = ((t_wall){fvec2_new(0, 0), -1, 13, 10, bricks});
	walls[18] = ((t_wall){fvec2_new(0, 0), 2, 12, 13, bricks});
	walls[19] = ((t_wall){fvec2_new(0, 0), -1, 13, 14, bricks});
	walls[20] = ((t_wall){fvec2_new(0, 0), 3, 14, 15, bricks});
	walls[21] = ((t_wall){fvec2_new(0, 0), -1, 15, 12, bricks});
	walls[22] = ((t_wall){fvec2_new(0, 0), 3, 14, 15, bricks});
	walls[23] = ((t_wall){fvec2_new(0, 0), -1, 15, 16, bricks});
	walls[24] = ((t_wall){fvec2_new(0, 0), -1, 16, 17, bricks});
	walls[25] = ((t_wall){fvec2_new(0, 0), -1, 17, 18, bricks});
	walls[26] = ((t_wall){fvec2_new(0, 0), -1, 18, 19, bricks});
	walls[27] = ((t_wall){fvec2_new(0, 0), -1, 19, 14, bricks});
	walls[28] = ((t_wall){fvec2_new(0, 0), -1, 19, 14, bricks});

	t_portal *portals = (t_portal *)malloc(4 * sizeof(t_portal));
	portals[0] = ((t_portal){0, 1, 9, 10, 8, 9, fence});
	portals[1] = ((t_portal){1, 2, 12, 14, 10, 11, NULL});
	portals[2] = ((t_portal){2, 3, 16, 18, 12, 13, NULL});
	portals[3] = ((t_portal){3, 4, 20, 22, 14, 15, NULL});

	t_sector *sectors = (t_sector *)malloc(5 * sizeof(t_sector));
	sectors[0] = ((t_sector){0, 10, 0, 0, 2.50, (t_color) {125, 125, 125, 255},
	skybox, tiles, fvec2_new(0, 0)});
	sectors[1] = ((t_sector){10, 4, 1, 0.4, 2.9, WHITE, skybox, tiles, fvec2_new(0, 0)});
	sectors[2] = ((t_sector){14, 4, 2, 0.8, 3.3, WHITE, skybox, tiles, fvec2_new(0, 0)});
	sectors[3] = ((t_sector){18, 4, 3, 1.2, 3.7, WHITE, skybox, tiles, fvec2_new(0, 0)});
	sectors[4] = ((t_sector){22, 6, 4, -30, 4.1, WHITE, skybox, tiles, fvec2_new(0, 0)});

	t_trigger *c_log = (t_trigger *)malloc(10 * sizeof(t_trigger));

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
		multi,
		1,
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
		multi,
		1
	});
	entities[2] = ((t_entity){
		2,
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
		multi,
		1
	});
	entities[3] = ((t_entity){
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
		key_card,
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
		(t_ph) {
			0.05,
			1.25,
			0,
			0,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0,
		},
		(t_ph) {
			0.05,
			1.25,
			0,
			0,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0,
		},
		90,
		{0, 1},
		6,
		0,
		inventory
	};

	// t_game_event *g_e = (t_game_event *)malloc(2 * sizeof(t_game_event));

	t_entity dummy = ((t_entity){
		3,
		(t_ph) {
			0,
			0,
			0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			1,
			0,
			0
		},
		(t_ph) {
			0,
			0,
			0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			1,
			0,
			0
		},
		sans,
		0
		});

	// T_ARRAY -> T_LIST needed :/

	t_game_event * first_e = (t_game_event *)malloc(sizeof(t_game_event));

	*first_e = (t_game_event){
		(t_elem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_TOUCH, entities[0] // Game event : list event wanted
			}
		};

	t_game_event * secon_e = (t_game_event *)malloc(sizeof(t_game_event));
	*secon_e = (t_game_event){
		(t_elem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_SEE, entities[1] // Game event : list event wanted
			}
		};

		t_game_event * kuadro_e = (t_game_event *)malloc(sizeof(t_game_event));
	*kuadro_e = (t_game_event){
		(t_elem) {NULL},
		(t_trigger){
			player.my_entity, TRIGGER_SEE, entities[0] // Game event : list event wanted
			}
		};

	t_game_event * third_e = (t_game_event *)malloc(sizeof(t_game_event));

	*third_e = (t_game_event){
		(t_elem) {NULL},
		(t_trigger){
			dummy, TRIGGER_SECTOR, dummy // Game event : list event wanted
			}
		};
	t_plist	g_e	= lpnew(secon_e);
	lppush(&g_e, first_e);
	lppush(&g_e, third_e);
	lppush(&g_e, kuadro_e);

	// t_array g_e = anew(NULL, 10, sizeof(t_game_event));

	// apush(&g_e, &(t_game_event){
	// 	(t_trigger){
	// 		player.my_entity, TRIGGER_TOUCH, entities[0] // Game event : list event wanted
	// 		}
	// 	});

	// apush(&g_e, &(t_game_event){
	// 	(t_trigger){
	// 		player.my_entity, TRIGGER_SEE, entities[1] // Game event : list event wanted
	// 		}
	// 	});

	// apush(&g_e, &(t_game_event){
	// 	(t_trigger){
	// 		dummy, TRIGGER_SECTOR, dummy // Game event : list event wanted
	// 		}
	// 	});

	t_music *music = (t_music *)malloc(2 * sizeof(t_music));
	music[0].music = Mix_LoadMUS("audio/test.ogg");
	music[1].music = Mix_LoadMUS("audio/test2.ogg");

	t_sound *sounds = (t_sound *)malloc(5 * sizeof(t_sound));
	sounds[0].sound = Mix_LoadWAV("audio/open_door.ogg");
	sounds[1].sound = Mix_LoadWAV("audio/dog.ogg");
	sounds[2].sound = Mix_LoadWAV("audio/oof.ogg");
	sounds[3].sound = Mix_LoadWAV("audio/touch.ogg");
	sounds[4].sound = Mix_LoadWAV("audio/salut.ogg");

	game.player = player;
	game.log = c_log;
	game.nlog = 10;
	game.waiting_events = g_e;
	game.nwaiting_events = 10;
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
	game.textures = textures;
	game.ntextures = 50;
	game.weapons = gun;
	game.nweapons = 7;
	game.played_music = 0;
	game.music = anew(NULL, 0, sizeof(t_music));
	game.sounds = anew(NULL, 0, sizeof(t_sound));
	game.chunks = anew(NULL, 0, sizeof(t_chunk));
	return (game);
}

