/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:15:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/07 07:12:29 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./graphic_project.h"

static t_proj	project_wall(t_ph physic, t_hit hit, t_sector sector[2], t_game game)
{
	t_proj		res;
	t_fvec2		h;
	t_fvec2		h2;
	t_fixed		top;
	t_fixed		bot;

	hit.u = (hit.u > 100) ? hit.u : 100;
	res.tex_proj.wall = game.walls[hit.wall];
	h = (t_fvec2) {
		f_from_float((physic.pos.z + physic.height) - sector[0].floor),
		f_from_float((physic.pos.z + physic.height) - sector[0].ceiling)};
	h2 = (t_fvec2) {
		f_from_float((physic.pos.z + physic.height) - sector[1].floor),
		f_from_float((physic.pos.z + physic.height) - sector[1].ceiling)};
	res.ceil = 0;
	res.step = 0;
	top = f_div(RATIO * h.v, hit.u) + physic.look_v * 100;
	bot = f_div(RATIO * h.u, hit.u) + physic.look_v * 100;
	if (res.tex_proj.wall.portal >= 0) {
		res.is_ceil = (h2.v - h.v > 0) ? 1 : 0;
		res.is_step = (h2.u - h.u < 0) ? 1 : 0;
		res.ceil = top + f_div(RATIO * (h2.v - h.v), hit.u);
		res.step = bot + f_div(RATIO * (h2.u - h.u), hit.u);
		res.ceil = f_to_int((f_from_int(HEIGHT) >> 1) + res.ceil);
		res.step = f_to_int((f_from_int(HEIGHT) >> 1) + res.step);
	}
	res.top = (f_from_int(HEIGHT) >> 1) + top;
	res.bot = (f_from_int(HEIGHT) >> 1) + bot;
	res.w_proj.tex_y_iter = f_div(f_from_int(1) << Y_PRECISION, res.bot - res.top);
	res.w_proj.tex_x = hit.t;
	res.top = f_to_int(res.top);
	res.bot = f_to_int(res.bot);
	res.tex_proj.sector = sector[0];
	res.h_proj.ray = hit.ray;
	res.h_proj.z_axis = physic.look_v;
	res.h_proj.pos = vec2_to_fvec2(vec3_to_vec2(physic.pos));
	res.h_proj.h = h;
	res.h_proj.ceiling = *sector[0].ceiling_mat;
	res.h_proj.floor = *sector[0].floor_mat;
	res.w_proj.wall = *res.tex_proj.wall.mat;
	return (res);
}

static t_hit	ray_wall(t_fvec2 q, t_i_wall wall, t_ph physic)
{
	const t_fvec2	p = fvec2_sub(wall.b, wall.a);
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(physic.pos));
	const t_fixed	denom = fvec2_cross(p, q).z;
	t_fixed			t;
	t_fixed			u;

	if (denom == 0)
		return ((t_hit) {-1, q, 0, 0});
	t = -f_div(f_mul(wall.a.u, q.v) - f_mul(pos.u, q.v) -\
		f_mul(q.u, wall.a.v) + f_mul(pos.v, q.u), denom);
	if (t > f_from_int(1) || t < 0)
		return ((t_hit) {-1, q, 0, 0});
	u = -f_div(-f_mul(wall.a.v, p.u) + f_mul(pos.v, p.u) +\
				f_mul(p.v, wall.a.u) - f_mul(pos.u, p.v), denom);
	if (u < 0)
		return ((t_hit) {-1, q, 0, 0});
	return ((t_hit) {wall.wall_id, q, t, u});
}

static t_proj	ray_sector(t_ray ray, t_sector sector, t_game game, t_color *buf)
{
	t_hit		hit;
	t_portal	portal;
	t_sector	p_sectors[2];
	t_wall		wall;
	t_i_wall	i_wall;

	i_wall.wall_id = sector.start;
	while (i_wall.wall_id < sector.start + sector.number)
	{
		if (ray.mask_wall == (ssize_t)i_wall.wall_id)
			++i_wall.wall_id;
		if (i_wall.wall_id >= sector.start + sector.number)
			break;
		wall = game.walls[i_wall.wall_id];
		i_wall.a = vec2_to_fvec2(game.points[wall.a]);
		i_wall.b = vec2_to_fvec2(game.points[wall.b]);
		hit = ray_wall(ray.dir, i_wall, game.player.physic);
		if (hit.wall >= 0)
		{
			if (wall.portal >= 0)
			{
				portal = game.portals[wall.portal];
				p_sectors[0] = sector;
				sector = (sector.sector_id == portal.from_sector) ?
					game.sectors[portal.to_sector] : game.sectors[portal.from_sector];
				ray.mask_wall = (sector.sector_id == portal.from_sector) ?
					portal.from_wall : portal.to_wall;
				p_sectors[1] = sector;
				render_wall(ray.id, project_wall(game.player.physic, hit, p_sectors, game), buf, game.frame);
				return (ray_sector(ray, sector, game, buf));
			}
			else
				return (project_wall(game.player.physic, hit, &sector, game));
		}
		++i_wall.wall_id;
	}
	return ((t_proj) {
		.tex_proj = (t_tex_proj) {sector, game.walls[sector.start]}
	});
}

void			raycast(t_game game, size_t sector_id, t_color *buf)
{
	const float		x_start = PWIDTH / 2;
	t_ray			ray;
	const t_sector	sector = game.sectors[sector_id];
	t_proj			proj;

	ray.id = 0;
	ray.mask_wall = -1;
	while (ray.id < WIDTH)
	{
		ray.dir = vec2_to_fvec2(
			vec2_rot((t_vec2){x_start - ray.id * (PWIDTH / WIDTH), PDIS},\
			game.player.physic.look_h));
		proj = ray_sector(ray, sector, game, buf);
		render_wall(ray.id, proj, buf, game.frame);
		ray.id++;
	}
}
