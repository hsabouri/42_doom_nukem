/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:51:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/18 12:24:37 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./graphic_project.h"

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
				render_wall(ray.id, projection(game.player.physic, hit, p_sectors, game), buf, game.frame);
				return (ray_sector(ray, sector, game, buf));
			}
			else
				return (projection(game.player.physic, hit, &sector, game));
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
