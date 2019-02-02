/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:52:36 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/02 17:09:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

/*

static void	collision_AABB(float *mouse, void *entity)
{
	if (mouse[0] >= entity.physic.pos_h.u && mouse[0] < entity.physic.pos_h.u +\
		entity.physic.width.v && mouse[1] >= entity.physic.pos_h.v && mouse[1] \
		< entity.physic.pos_h.v + entity.physic.height.v)
		return ("headshot");
	else if (mouse[0] >= entity.physic.pos.u && mouse[0] < entity.physic.pos.u \
		+ entity.physic.pos.width.u && mouse[1] >= entity.physic.pos.v && \
		mouse[1] < entity.physic.pos.v + entity.physic.height.u)
		return ("bodyshot");
}

static void	nearest_entity(t_player player, float *enemy1, float *enemy2)
{
	if ((abs(enemy1[0] - player.x) <= abs(enemy2[0]- player.x) && abs(enemy1[1]\
		- player.y) <= abs(enemy1[1] - player.y)) || (abs(enemy1[0] - player.x)\
		<= abs(enemy2[2] - player.x) && abs(enemy1[2] - player.y) <= \
		abs(enemy2[3] - player.y)))
			return (1);
	return (0);
}

static void	entities_collision(float *mouse, t_game game, t_player player)
{
	int 	i;
	int 	nearest;
	float	entity_1[4];
	float	entity_2[4];

	i = -1;
	nearest = 0;
	while (i < game.nentities)
	{
		entity_1[0] = (collision_AABB(mouse, game.entities[i] == "headshot") ?
					game.entities[i].physic.pos_h.u : entities[i].physic.pos.u;
		entity_1[1] = (collision_AABB(mouse, game.entities[i] == "headshot") ?
					game.entities[i].physic.pos_h.v : entities[i].physic.pos.v;
		entity_1[3] = game.entities[i].physic.pos.u;
		entity_1[4] = game.entities[i].physic.pos.v;
		entity_2[0] = game.entities[nearest].physic.pos.u;
		entity_2[1] = game.entities[nearest].physic.pos.v;
		entity_2[3] = game.entities[nearest].physic.pos_h.u;
		entity_2[4] = game.entities[nearest].physic.pos_h.v;
		if (nearest_entity(player, entity_1, entity_2) == 1)
			nearest = i;
	}
}

void			check_shot(t_game game, float mouse_x, float mouse_y)
{
	int		i;
	float	mouse[2];
	// t_array	shot;

	i = -1;
	mouse[0] = mouse_x;
	mouse[1] = mouse_y
	// shot = anew(NULL, 1, sizeof(t_shot));
	entities_collision(mouse, game, game.player);
}

*/