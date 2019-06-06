/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <iporsenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:22:20 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/29 16:00:43 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int			seg_seg(t_vec3 next_pos, t_ph physic, t_touch *touch, t_game game)
{
	t_vec2	ab;
	t_vec2	cd;
	float	denom;
	float	dist[2];

	ab = vec2_new(game.points[game.walls[touch->wall].b].u
		- game.points[game.walls[touch->wall].a].u,
		game.points[game.walls[touch->wall].b].v
		- game.points[game.walls[touch->wall].a].v);
	cd = vec2_new(next_pos.x - physic.pos.x, next_pos.y - physic.pos.y);
	denom = vec2_cross(ab, cd).z;
	if (denom < -0.0001 && denom > 0.0001)
		return (-1);
	dist[0] = -(game.points[game.walls[touch->wall].a].u * cd.v
		- physic.pos.x * cd.v - cd.u * game.points[game.walls[touch->wall].a].v
		+ cd.u * physic.pos.y) / denom;
	if (dist[0] < 0 || dist[0] > 1)
		return (0);
	dist[1] = -(-ab.u * game.points[game.walls[touch->wall].a].v + ab.u
		* physic.pos.y + ab.v * game.points[game.walls[touch->wall].a].u
		- ab.v * physic.pos.x) / denom;
	if (dist[1] < 0 || dist[1] > 1)
		return (0);
	touch->dist = dist[1];
	return (1);
}

t_touch		collision(t_vec3 next_pos, t_ph physic, t_game game, int wall)
{
	int		end;
	t_touch	touch;

	end = game.sectors[physic.sector_id].start
		+ game.sectors[physic.sector_id].number;
	touch.wall = game.sectors[physic.sector_id].start;
	touch.dist = 0;
	while (touch.wall < end)
	{
		if (touch.wall != wall && seg_seg(next_pos, physic, &touch, game) == 1)
			return (touch);
		touch.wall++;
	}
	touch.wall = -1;
	return (touch);
}

t_vec3		floor_col(float pos_z, t_sector sector, t_vec3 speed,
u_int32_t *jump)
{
	t_vec3	final_speed;
	float	delta;

	final_speed = speed;
	delta = pos_z - sector.floor.z;
	if (delta < -0.0001)
	{
		final_speed.z = speed.z - delta;
		final_speed.x = final_speed.z / speed.z * speed.x;
		final_speed.y = final_speed.z / speed.z * speed.y;
		if (*jump)
			jump = 0;
		return (final_speed);
	}
	return (final_speed);
}

t_vec3		ceil_col(t_vec3 pos, t_sector sector, t_vec3 speed)
{
	t_vec3	final_speed;
	float	delta;
	float	z;

	final_speed = speed;
	z = z_inter(sector, pos, 0);
	delta = z - pos.z;
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

	line_vector = vec2_sub(game.points[wall.b], game.points[wall.a]);
	v2_normal.u = line_vector.v;
	v2_normal.v = -line_vector.u;
	v2_normal = vec2_normalize(v2_normal);
	d = vec2_dot(v2_normal, game.points[wall.a]);
	v3_normal = vec2_to_vec3(v2_normal);
	dist[0] = vec3_dot(v3_normal, game.player.my_entity.physic.pos) - d;
	if (dist[0] < 0)
	{
		v3_normal = vec3_scale(v3_normal, -1);
		d = -d;
	}
	dist[1] = vec3_dot(v3_normal, next_pos) - d;
	if (dist[1] < 0)
		next_pos = vec3_add(next_pos, vec3_scale(v3_normal, -dist[1] + 0.1));
	return (next_pos);
}
