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

static int	seg_seg(t_vec3  next_pos, t_player player, t_touch *touch, t_game game)
{
	t_vec2	AB;
	t_vec2	CD;
	float	denom;
	float	dist[2];

	AB = vec2_new(game.points[game.walls[touch->wall].b].u - \
					game.points[game.walls[touch->wall].a].u, \
					game.points[game.walls[touch->wall].b].v - \
					game.points[game.walls[touch->wall].a].v);
	CD = vec2_new(next_pos.x - player.physic.pos.x, \
					next_pos.y - player.physic.pos.y);
	denom = vec2_cross(AB, CD).z;
	if (denom < -0.0001 && denom > 0.0001)
		return (-1);
	dist[0] = -(game.points[game.walls[touch->wall].a].u * CD.v - player.physic.pos.x * \
		CD.v - CD.u * game.points[game.walls[touch->wall].a].v + CD.u * \
		player.physic.pos.y) / denom;
	if (dist[0] < 0 || dist[0] > 1)
		return (0);
	dist[1] = -(-AB.u * game.points[game.walls[touch->wall].a].v + AB.u * \
		player.physic.pos.y + AB.v * game.points[game.walls[touch->wall].a].u - \
		AB.v * player.physic.pos.x) / denom;
	if (dist[1] < 0 || dist[1] > 1)
		return (0);
	touch->dist = dist[1];
	return (1);
}

t_touch		collision(t_vec3 next_pos, t_game game, u_int32_t *sector_id, int wall)
{
	int		end;
	t_touch	touch;

	end = game.sectors[*sector_id].start + game.sectors[*sector_id].number;
	touch.wall = game.sectors[*sector_id].start;
	touch.dist = 0;
	while (touch.wall < end)
	{
		if (touch.wall != wall && seg_seg(next_pos, game.player, &touch, game) == 1)
			return (touch);
		touch.wall++;
	}
	touch.wall = -1;
	return (touch);
}

t_vec3		floor_col(float pos_z, t_sector sector, t_vec3 speed)
{
	t_vec3	final_speed;
	float	delta;

	final_speed = speed;
	delta = pos_z - sector.floor;
	if (delta < -0.0001)
	{
		final_speed.z = speed.z - delta;
		final_speed.x = final_speed.z / speed.z * speed.x;
		final_speed.y = final_speed.z / speed.z * speed.y;
		return (final_speed);
	}
	return (final_speed);
}

t_vec3		ceil_col(float pos_z, t_sector sector, t_vec3 speed)
{
	t_vec3	final_speed;
	float	delta;

	final_speed = speed;
	delta = sector.ceiling - pos_z;
	if (delta < -0.05)
	{
		final_speed.z = speed.z + (delta - 0.05);
		final_speed.x = final_speed.z / speed.z * speed.x;
		final_speed.y = final_speed.z / speed.z * speed.y;
		return (final_speed);
	}
	return (final_speed);
}

t_vec3		slide_wall(t_vec3 next_pos, t_game game, t_wall wall)
{
	t_vec2		line_vector;
	t_vec2		v2_normal;
	t_vec3		v3_normal;
	float		d;
	float		dist[2];

	line_vector = vec2_sub(game.points[wall.b], \
							game.points[wall.a]);
	v2_normal.u = line_vector.v;
	v2_normal.v = -line_vector.u;
	v2_normal = vec2_normalize(v2_normal);
	d = vec2_dot(v2_normal, game.points[wall.a]);
	v3_normal = vec2_to_vec3(v2_normal);
	dist[0] = vec3_dot(v3_normal, game.player.physic.pos) - d;
	if (dist[0] < 0)
	{
		v3_normal = vec3_scale(v3_normal, -1);
		d = -d;
	}
	dist[1] = vec3_dot(v3_normal, next_pos) - d;
	if (dist[1] < 0)
		next_pos = vec3_add(next_pos, vec3_scale(v3_normal, -dist[1] + 0.01));
	return (next_pos);
}