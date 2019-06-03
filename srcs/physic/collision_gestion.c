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

t_vec3		floor_col(t_vec3 pos, t_sector sector, t_vec3 speed,
u_int32_t *jump)
{
	t_vec3	final_speed;
	float	z_floor;
	float	delta;
	t_vec3 z;
	t_fixed t;
	t_line line;

	final_speed = pos;
	z_floor = z_entity(sector, pos, 1);
	if (z_floor <= 0)
		delta = pos.z - z_floor;
	else
		delta = z_floor - pos.z;
	if (delta < -0.0001)
	{
	
		z.x = pos.x + speed.x;
		z.y = pos.y + speed.y;
		z.z = pos.z;
		line.x.v = f_from_float(speed.x);
		line.y.v = f_from_float(speed.y);
		line.z.v = f_from_float(speed.z);
		line.x.u = f_from_float(pos.x - sector.center.u);
		line.y.u = f_from_float(pos.y - sector.center.v);
		line.z.u = f_from_float(pos.z);
		// printf("| %f + %fx | %f + %fy | %f + %f z\n", f_to_float(line.x.u), f_to_float(line.x.v), f_to_float(line.y.u),
	// f_to_float(line.y.v), f_to_float(line.z.u), f_to_float(line.z.v));
		t = f_mul(sector.floor.x, line.x.v) + f_mul(sector.floor.y,
			line.y.v) - line.z.v;
		if ( t == 0 || (sector.floor.x == 0 && sector.floor.y == 0))
			return(z);
		t = f_div((-sector.floor.z - f_mul(sector.floor.x, line.x.u)
		- f_mul(sector.floor.y, line.y.u) + line.z.u),
		(f_mul(sector.floor.x, line.x.v) + f_mul(sector.floor.y,
			line.y.v) - line.z.v));
		z.x = f_to_float(line.x.u + f_mul(t, line.x.v));
		z.y = f_to_float(line.y.u + f_mul(t, line.y.v));
		z.z = f_to_float(line.z.u + f_mul(t, line.z.v));
		if (*jump)
			jump = 0;
		printf("| Z | x = %f y = %f z = %f\n",z.x,z.y,z.z);
		final_speed = z;
		return(final_speed);
	}
	return (final_speed);
}

t_vec3		ceil_col(t_vec3 pos, t_sector sector, t_vec3 speed)
{
	t_vec3	final_speed;
	float	z;
	float	delta;

	final_speed = speed;
	z = z_entity(sector, pos, 0);
	delta = z - pos.z;
	if (z <= 0)
		delta = pos.z - z;
	else
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
