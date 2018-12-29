/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:22:20 by iporsenn          #+#    #+#             */
/*   Updated: 2018/12/22 18:22:21 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static int	seg_seg(t_vec3  next_pos, t_player player, t_wall wall, t_game game)
{
	t_vec2	AB;
	t_vec2	CD;
	float	denom;
	float	t;
	float	u;

	AB = vec2_new(game.points[wall.a].u - game.points[wall.b].u,\
					game.points[wall.a].v - game.points[wall.b].v);
	CD = vec2_new(next_pos.x - player.physic.pos.x, \
					next_pos.y - player.physic.pos.y);
	denom = vec2_dot(AB, CD);
	if (denom == 0)
		return (-1);
	t = -(game.points[wall.a].u * CD.v - player.physic.pos.x * CD.v - CD.u * \
		game.points[wall.a].v + CD.u * player.physic.pos.y) / denom;
	if (t < 0 || t >= 1)
		return (0);
	u = -(-AB.u * game.points[wall.a].v + AB.u * player.physic.pos.y + AB.v * \
		game.points[wall.a].u - AB.v * player.physic.pos.x) / denom;
	if (u < 0 || u >= 1)
		return (0);
	return (1);
}

int			collision(t_vec3 next_pos, t_game game, t_player player)
{
	t_array		sub_walls;
	int			nbr_inter;
	size_t		cpt;

	// sub_walls.first = anth(game.sectors, game.player.id);
	// sub_walls.mem = subs_walls.first;
	// sub_walls.len = (t_sector *)anth(&game.sectors, game.player.id)->number;
	// sub_walls.elem_size = sizeof(t_wall);
	// sub_walls.allocated = sub_walls.elem_size * sub_walls.len;
	cpt = -1;
	while (++cpt < game.walls.len)
	{
		if (seg_seg(next_pos, player, game.walls[cpt], game) == 1)
			nbr_inter++;
		// else if (seg_seg(next_pos, game.player, sub_walls[cpt], game) == 1 && \
		// 		sub_walls[cpt].portal >= 0)
		// {
		// 		player.pos = teleportation(player, sub_walls[cpt].portal, \
		// 						walls[sub_walls[cpt].to_wall].portal);
		// 		player.id = sub_walls[cpt].to_sector;
		// 		break;
		// }
	}
	if (nbr_inter != 0)
		return (1);
	return (0);
}
