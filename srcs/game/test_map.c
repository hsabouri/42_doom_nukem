/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/03/04 16:11:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(t_game game)
{
	t_player player = (t_player) {
		(t_ph) {
			0.02,
			1.25,
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
			0.02,
			1.25,
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

	t_img *textures = (t_img *)malloc(4 * sizeof(t_img));
	textures[0] = parse_tga("./textures/wall.tga");
	textures[1] = parse_tga("./textures/licorne.tga");
	textures[2] = parse_tga("./textures/floor.tga");
	textures[3] = parse_tga("./textures/player.tga");

	t_mat *materials = (t_mat *)malloc(7 * sizeof(t_mat));
	materials[0] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		(t_color){0xFF, 0x00, 0x60, 0xFF},
		NULL,
		TILING,
		WHITE,
		NULL
	};
	materials[1] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		(t_color){0xFF, 0x00, 0x06, 0xFF},
		textures,
		TILING,
		(t_color) {255, 255, 255, 255},
		NULL
	};
	materials[2] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		(t_color){0xFF, 0x00, 0x06, 0xFF},
		textures,
		TILING,
		RED,
		&materials[3]
	};
	materials[3] = (t_mat) {
		fvec2_new(f_from_float(0.5), f_from_float(0.5)),
		fvec2_new(f_from_int(2), f_from_int(2)),
		NO_COLOR,
		&textures[1],
		NO_TILING,
		WHITE,
		NULL
	};
	materials[4] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1) >> 1, f_from_int(1) >> 1),
		NO_COLOR,
		&textures[2],
		TILING,
		WHITE,
		NULL
	};
	materials[5] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(10)),
		NO_COLOR,
		&textures[0],
		TILING,
		WHITE,
		NULL
	};
	materials[6] = (t_mat) {
		fvec2_new(0, 0),
		fvec2_new(f_from_int(1), f_from_int(1)),
		NO_COLOR,
		&textures[3],
		NO_TILING,
		WHITE,
		NULL
	};

	t_wall *walls = (t_wall *)malloc(28 * sizeof(t_wall));
	walls[0] = ((t_wall){-1, 9, 0, &materials[1]});
	walls[1] = ((t_wall){-1, 0, 1, &materials[1]});
	walls[2] = ((t_wall){-1, 1, 2, &materials[2]});
	walls[3] = ((t_wall){-1, 2, 3, &materials[1]});
	walls[4] = ((t_wall){-1, 3, 4, &materials[1]});
	walls[5] = ((t_wall){-1, 4, 5, &materials[1]});
	walls[6] = ((t_wall){-1, 5, 6, &materials[1]});
	walls[7] = ((t_wall){-1, 6, 7, &materials[1]});
	walls[8] = ((t_wall){-1, 7, 8, &materials[1]});
	walls[9] = ((t_wall){0, 8, 9, &materials[1]});
	walls[10] = ((t_wall){0, 8, 9, &materials[1]});
	walls[11] = ((t_wall){-1, 9, 10, &materials[1]});
	walls[12] = ((t_wall){-1, 8, 11, &materials[1]});
	walls[13] = ((t_wall){1, 10, 11, &materials[1]});
	walls[14] = ((t_wall){1, 10, 11, &materials[1]});
	walls[15] = ((t_wall){-1, 11, 12, &materials[1]});
	walls[16] = ((t_wall){-1, 10, 13, &materials[1]});
	walls[17] = ((t_wall){2, 12, 13, &materials[1]});
	walls[18] = ((t_wall){2, 12, 13, &materials[1]});
	walls[19] = ((t_wall){-1, 13, 14, &materials[1]});
	walls[20] = ((t_wall){-1, 12, 15, &materials[1]});
	walls[21] = ((t_wall){3, 14, 15, &materials[1]});
	walls[22] = ((t_wall){3, 14, 15, &materials[5]});
	walls[23] = ((t_wall){-1, 15, 16, &materials[5]});
	walls[24] = ((t_wall){-1, 16, 17, &materials[5]});
	walls[25] = ((t_wall){-1, 17, 18, &materials[5]});
	walls[26] = ((t_wall){-1, 18, 19, &materials[5]});
	walls[27] = ((t_wall){-1, 19, 14, &materials[5]});

	t_portal *portals = (t_portal *)malloc(4 * sizeof(t_portal));
	portals[0] = ((t_portal){0, 1, 9, 10, 8, 9});
	portals[1] = ((t_portal){1, 2, 13, 14, 10, 11});
	portals[2] = ((t_portal){2, 3, 17, 18, 12, 13});
	portals[3] = ((t_portal){3, 4, 21, 22, 14, 15});

	t_sector *sectors = (t_sector *)malloc(5 * sizeof(t_sector));
	sectors[0] = ((t_sector){0, 10, 0, 0, 2.50, (t_color) {125, 125, 125, 255},
		&materials[1], &materials[4]});
	sectors[1] = ((t_sector){10, 4, 1, 0.4, 2.9, WHITE, &materials[1], &materials[4]});
	sectors[2] = ((t_sector){14, 4, 2, 0.8, 3.3, WHITE, &materials[1], &materials[4]});
	sectors[3] = ((t_sector){18, 4, 3, 1.2, 3.7, WHITE, &materials[1], &materials[4]});
	sectors[4] = ((t_sector){22, 6, 4, -30, 4.1, WHITE, &materials[1], &materials[4]});

	game.entities = (t_test_entity *)malloc(10 * sizeof(t_test_entity));
	game.entities[0] = (t_test_entity) {
		(t_ph) {
			0.02,
			1.25,
			(t_vec3){4, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		1,
		&materials[6]
	};

	game.entities[1] = (t_test_entity) {
		(t_ph) {
			0.02,
			1,
			(t_vec3){2, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		0.5,
		&materials[6]
	};

	game.entities[2] = (t_test_entity) {
		(t_ph) {
			0.02,
			1,
			(t_vec3){4.5, 5, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			1,
			0,
			0
		},
		0.5,
		&materials[6]
	};

	game.nentities = 3;
	game.player = player;
	game.sectors = sectors;
	game.nsectors = 5;
	game.walls = walls;
	game.nwalls = 28;
	game.portals = portals;
	game.nportals = 4;
	game.points = points;
	game.npoints = 20;
	game.textures = textures;
	game.ntextures = 4;
	game.materials = materials;
	game.nmaterials = 7;
	return (game);
}
