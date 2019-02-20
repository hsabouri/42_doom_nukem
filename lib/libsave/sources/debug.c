/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:03:31 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/19 16:03:34 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

void		debug(t_game game)
{
	int	i;

	// printf("player.physic.gravity: %f\n", game.player.physic.gravity);
	// printf("player.physic.height: %f\n", game.player.physic.height);
	// printf("player.physic.pos: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	// printf("player.physic.speed_max: {%f, %f, %f}\n", game.player.physic.speed_max.x, game.player.physic.speed_max.y, game.player.physic.speed_max.z);
	// printf("player.physic.look: {%f, %f}\n", game.player.physic.look.u, game.player.physic.look.v);

	i = 0;
	while (i < (int)game.npoints)
	{
		printf("points[i].x: %f, point[i].y: %f\n", game.points[i].u, game.points[i].v);
		i++;
	}
	printf("nmats: %zu\n", game.nmaterials);
}
