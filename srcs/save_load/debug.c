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

#include <doom.h>

void		debug(t_game game)
{
	int	i;

	// printf("player.physic.gravity: %f\n", game.player.physic.gravity);
	// printf("player.physic.height: %f\n", game.player.physic.height);
	// printf("player.physic.radius: %f\n", game.player.physic.radius);
	// printf("player.physic.pos: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	// printf("player.physic.speed_max: {%f, %f, %f}\n", game.player.physic.speed_max.x, game.player.physic.speed_max.y, game.player.physic.speed_max.z);
	// printf("player.physic.look: {%f, %f}\n", game.player.physic.look_h, f_to_float(game.player.physic.look_v));
	// printf("player.physic.sector_id: %u\n", game.player.physic.sector_id);

	i = 0;
	while (i < (int)game.nentities)
	{
		printf("entities.physic.gravity: %f\n", game.entities->physic.gravity);
		printf("entities.physic.height: %f\n", game.entities->physic.height);
		printf("entities.physic.radius: %f\n", game.entities->physic.radius);
		printf("entities.physic.pos: {%f, %f, %f}\n", game.entities->physic.pos.x, game.entities->physic.pos.y, game.entities->physic.pos.z);
		printf("entities.physic.speed_max: {%f, %f, %f}\n", game.entities->physic.speed_max.x, game.entities->physic.speed_max.y, game.entities->physic.speed_max.z);
		printf("entities.physic.look: {%f, %f}\n", game.entities->physic.look_h, f_to_float(game.entities->physic.look_v));
		printf("entities.physic.sector_id: %u\n", game.entities->physic.sector_id);
		i++;
	}
	printf("nentities: %zu\n", game.nentities);
}
