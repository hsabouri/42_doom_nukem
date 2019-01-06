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
	t_vec3	denom;
	float	t;
	float	u;

	AB = vec2_new(game.points[wall.b].u - game.points[wall.a].u,\
					game.points[wall.b].v - game.points[wall.a].v);
	CD = vec2_new(next_pos.x - player.physic.pos.x, \
					next_pos.y - player.physic.pos.y);
	denom = vec2_cross(AB, CD);
	if (denom.z == 0)
		return (-1);
	t = -(game.points[wall.a].u * CD.v - player.physic.pos.x * CD.v - CD.u * \
		game.points[wall.a].v + CD.u * player.physic.pos.y) / denom.z;
	if (t < 0 || t > 1)
		return (0);
	u = -(-AB.u * game.points[wall.a].v + AB.u * player.physic.pos.y + AB.v * \
		game.points[wall.a].u - AB.v * player.physic.pos.x) / denom.z;
	if (u < 0 || u > 1)
		return (0);
	return (1);
}

int			collision(t_vec3 next_pos, t_game game, u_int32_t *sector_id, int wall)
{
	int		cpt;
	int		len;

	cpt = game.sectors[*sector_id].start;
	len = game.sectors[*sector_id].start + game.sectors[*sector_id].number;
	while (cpt < len)
	{
		if (cpt != wall && seg_seg(next_pos, game.player, game.walls[cpt], game) == 1)
			return (cpt);
		cpt++;
	}
	return (-1);
}
