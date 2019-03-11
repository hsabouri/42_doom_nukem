/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:03:31 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/11 18:19:10 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

void		debug(t_game game)
{
	int	i;

	// printf("player.my_entity.physic.gravity: %f\n", game.player.my_entity.physic.gravity);
	// printf("player.my_entity.physic.height: %f\n", game.player.my_entity.physic.height);
	// printf("player.my_entity.physic.radius: %f\n", game.player.my_entity.physic.radius);
	// printf("player.my_entity.physic.pos: {%f, %f, %f}\n", game.player.my_entity.physic.pos.x, game.player.my_entity.physic.pos.y, game.player.my_entity.physic.pos.z);
	// printf("player.my_entity.physic.speed_max: {%f, %f, %f}\n", game.player.my_entity.physic.speed_max.x, game.player.my_entity.physic.speed_max.y, game.player.my_entity.physic.speed_max.z);
	// printf("player.my_entity.physic.look: {%f, %f}\n", game.player.my_entity.physic.look_h, f_to_float(game.player.my_entity.physic.look_v));
	// printf("player.my_entity.physic.sector_id: %u\n", game.player.my_entity.physic.sector_id);

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
