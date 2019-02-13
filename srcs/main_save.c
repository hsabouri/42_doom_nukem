/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:08:23 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/11 11:08:25 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int		main_save(char *name)
{
	t_game		game;
	// t_player	player;
	// t_vec2		*points;

	// player = player_default();
	// game.npoints = 20;
	// points = (t_vec2 *)malloc(sizeof(t_vec2) * 20);
	// points[0] = ((t_vec2){7, 6});
	// points[1] = ((t_vec2){8, 7});
	// points[2] = ((t_vec2){8, 11});
	// points[3] = ((t_vec2){5, 12});
	// points[4] = ((t_vec2){4, 12});
	// points[5] = ((t_vec2){1, 11});
	// points[6] = ((t_vec2){1, 7});
	// points[7] = ((t_vec2){2, 6});
	// points[8] = ((t_vec2){4, 6});
	// points[9] = ((t_vec2){5, 6});
	// points[10] = ((t_vec2){5, 4.5});
	// points[11] = ((t_vec2){4, 4});
	// points[12] = ((t_vec2){6, 2});
	// points[13] = ((t_vec2){6.5, 3});
	// points[14] = ((t_vec2){7, 3});
	// points[15] = ((t_vec2){7, 2});
	// points[16] = ((t_vec2){8, 0});
	// points[17] = ((t_vec2){9, 0});
	// points[18] = ((t_vec2){9, 5});
	// points[19] = ((t_vec2){8, 5});
	// game.player = player;
	// game.points = points;
	// save(name, game);
	game = load(name);
	return (0);
}
