/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/04/14 17:25:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(void)
{
	t_game game;
	
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
			0
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
			0
		}
	};

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

	t_img *textures = (t_img *)malloc(13 * sizeof(t_img));
	textures[0] = parse_tga("./textures/wall.tga");
	textures[1] = parse_tga("./textures/floor.tga");
	textures[2] = parse_tga("./textures/player.tga");
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

	materials[3] = (t_mat) { // Sans
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[2],
		NO_TILING,
		WHITE,
		NULL
	};
	t_mat *sans = &materials[3];

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

	t_entity *entities = (t_entity *)malloc(3 * sizeof(t_entity));
	entities[0] = ((t_entity){
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
		0
	});
	entities[1] = ((t_entity){
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

	game.player = player;
	game.entities = entities;
	game.nentities = 3;
	game.sectors = sectors;
	game.nsectors = 5;
	game.walls = walls;
	game.nwalls = 29;
	game.nuwalls = 0;
	game.portals = portals;
	game.nportals = 4;
	game.points = points;
	game.npoints = 20;
	game.textures = textures;
	game.ntextures = 13;
	game.materials = materials;
	game.nmaterials = 16;
	game.played_music = 0;
	game.music = anew(NULL, 0, sizeof(t_music));
	game.sounds = anew(NULL, 0, sizeof(t_sound));
	game.chunks = anew(NULL, 0, sizeof(t_chunk));
	return (game);
}

