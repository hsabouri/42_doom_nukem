/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2019/01/16 19:21:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(t_game game)
{
	t_player player = (t_player) {
		(t_ph) {
			0.5,
			1.25,
			(t_vec3){7, 9, 50},
			(t_vec3){0, 0, 0},
			(t_vec3){8, 8, 53},
			(t_vec2){0, 0},
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

	t_wall *walls = (t_wall *)malloc(28 * sizeof(t_wall));
	walls[0] = ((t_wall){-1, 9, 0, BLUE});
	walls[1] = ((t_wall){-1, 0, 1, GREEN});
	walls[2] = ((t_wall){-1, 1, 2, RED});
	walls[3] = ((t_wall){-1, 2, 3, BLUE});
	walls[4] = ((t_wall){-1, 3, 4, GREEN});
	walls[5] = ((t_wall){-1, 4, 5, RED});
	walls[6] = ((t_wall){-1, 5, 6, BLUE});
	walls[7] = ((t_wall){-1, 6, 7, GREEN});
	walls[8] = ((t_wall){-1, 7, 8, RED});
	walls[9] = ((t_wall){0, 8, 9, BLUE});
	walls[10] = ((t_wall){0, 8, 9, GREEN});
	walls[11] = ((t_wall){-1, 9, 10, RED});
	walls[12] = ((t_wall){-1, 8, 11, BLUE});
	walls[13] = ((t_wall){1, 10, 11, GREEN});
	walls[14] = ((t_wall){1, 10, 11, RED});
	walls[15] = ((t_wall){-1, 11, 12, BLUE});
	walls[16] = ((t_wall){-1, 10, 13, GREEN});
	walls[17] = ((t_wall){2, 12, 13, RED});
	walls[18] = ((t_wall){2, 12, 13, BLUE});
	walls[19] = ((t_wall){-1, 13, 14, GREEN});
	walls[20] = ((t_wall){-1, 12, 15, RED});
	walls[21] = ((t_wall){3, 14, 15, BLUE});
	walls[22] = ((t_wall){3, 14, 15, GREEN});
	walls[23] = ((t_wall){-1, 15, 16, RED});
	walls[24] = ((t_wall){-1, 16, 17, BLUE});
	walls[25] = ((t_wall){-1, 17, 18, GREEN});
	walls[26] = ((t_wall){-1, 18, 19, RED});
	walls[27] = ((t_wall){-1, 19, 14, BLUE});

	t_portal *portals = (t_portal *)malloc(4 * sizeof(t_portal));
	portals[0] = ((t_portal){0, 1, 9, 10, 8, 9});
	portals[1] = ((t_portal){1, 2, 13, 14, 10, 11});
	portals[2] = ((t_portal){2, 3, 17, 18, 12, 13});
	portals[3] = ((t_portal){3, 4, 21, 22, 14, 15});

	t_sector *sectors = (t_sector *)malloc(5 * sizeof(t_sector));
	sectors[0] = ((t_sector){0, 10, 0, 0, 2.50});
	sectors[1] = ((t_sector){10, 4, 1, 0.4, 2.9});
	sectors[2] = ((t_sector){14, 4, 2, 0.8, 3.3});
	sectors[3] = ((t_sector){18, 4, 3, 1.2, 3.7});
	sectors[4] = ((t_sector){22, 6, 4, -30, 4.1});

	t_img *textures = (t_img *)malloc(1 * sizeof(t_img));
	textures[0] = parse_tga("./textures/licorne.tga");

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
	game.ntextures = 2;
	return (game);
}
