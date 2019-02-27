/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:49:30 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/25 1:48:29 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphic_v2.h"

typedef struct	s_bunch
{
	int				nwalls;
	t_cache_wall	walls[NCACHEWALL];
}				t_bunch;

t_fvec2	get_ray_dir(t_ph physic, int id)
{
	return (vec2_to_fvec2(vec2_rot((t_vec2) {
		(-PWIDTH / 2) + id * (PWIDTH / WIDTH), PDIS},
		physic.look_h)));
}

t_limit	build_limits(t_context context)
{
	t_limit		limit_rays;

	limit_rays.left.dir = get_ray_dir(context.physic, context.left);
	limit_rays.left.id = context.left;
	limit_rays.left.mask_wall = context.mask;
	limit_rays.right.dir = get_ray_dir(context.physic, context.right);
	limit_rays.right.id = context.right;
	limit_rays.right.mask_wall = context.mask;
	return (limit_rays);
}

/*********************************************************************************
 * BUNCH CALCULATION
*********************************************************************************/

static inline int		is_in_limit(t_fvec2 left, t_fvec2 right, t_fvec2 a, t_fvec2 b)
{
	return (!((fvec2_cross(left, a).z >= 0 && fvec2_cross(left, b).z >= 0) ||
		(fvec2_cross(right, a).z <= 0 && fvec2_cross(right, b).z <= 0)));
}

t_bunch	build_bunch(t_game game, t_context context, t_limit limit)
{
	t_bunch			ret;
	t_cache_wall	current;
	const t_sector	sector = game.sectors[context.sector.sector_id];
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	size_t			i;

	ret.nwalls = 0;
	i = sector.start;
	while (i < sector.start + sector.number)
	{
		current.a = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].a]), pos);
		current.b = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].b]), pos);
		if ((size_t)context.mask != i &&
			is_in_limit(limit.left.dir, limit.right.dir, current.a, current.b))
		{
			current.id = i;
			current.portal = game.walls[i].portal;
			current.mat = *game.walls[i].mat;
			ret.walls[ret.nwalls] = current;
			++ret.nwalls;
		}
		++i;
	}
	return (ret);
}

/*********************************************************************************
*********************************************************************************/

/*********************************************************************************
 * RAY CALCULATION
*********************************************************************************/

t_hit	ray_seg(t_fvec2 a, t_fvec2 b, t_fvec2 c, t_fvec2 d)
{
	const t_fvec2	p = fvec2_sub(b, a);
	const t_fvec2	q = fvec2_sub(d, c);
	t_fvec2			ratios;
	const t_fixed	denom = fvec2_cross(p, q).z;

	if (denom == 0)
		return ((t_hit) {0, fvec2_new(0, 0)});
	ratios.u = -f_div(f_mul(a.u, q.v) - f_mul(c.u, q.v) -
		f_mul(q.u, a.v) + f_mul(c.v, q.u), denom);
	ratios.v = -f_div(-f_mul(a.v, p.u) + f_mul(c.v, p.u) +
		f_mul(p.v, a.u) - f_mul(c.u, p.v), denom);
	return ((t_hit) {1, ratios});
}

int		is_left(t_fvec2 a, t_fvec2 b)
{
	return (fvec2_cross(a, b).z >= 0);
}

t_fvec2	take_left(t_fvec2 a, t_fvec2 b)
{
	if (is_left(a, b))
		return (b);
	else
		return (a);
}

t_fvec2	take_right(t_fvec2 a, t_fvec2 b)
{
	if (!is_left(a, b))
		return (b);
	else
		return (a);
}

int		get_ray_id(t_fvec2 point, t_limit limit, t_context context, int max)
{
	t_hit	col;
	int		id;
	
	col = ray_seg(fvec2_new(0, 0), point, limit.left.dir, limit.right.dir);
	if (col.ratios.v <= 0 || col.ratios.v >= f_from_int(1) || col.ratios.u < 0)
		id = max;
	else
		id = context.left + f_to_int(col.ratios.v * (context.right - context.left));
	return (id);
}

t_render		build_sections(t_context context, t_bunch bunch,
t_limit limits)
{
	t_cache_wall	current;
	t_section		current_section;
	t_render		render;

	render.nsections = 0;
	while (render.nsections < bunch.nwalls)
	{
		current = bunch.walls[render.nsections];
		current_section.wall = current;
		current_section.start = get_ray_id(take_left(current.a, current.b),
			limits, context, context.left);
		current_section.end = get_ray_id(take_right(current.a, current.b),
			limits, context, context.right);
		/*
		current_section.a = ray_seg( take_left(current.a, current.b),
			take_right(current.a, current.b), fvec2_new(0, 0),
			get_ray_dir(context.physic, current_section.start)
		).ratios;
		current_section.b = ray_seg( take_left(current.a, current.b),
			take_right(current.a, current.b), fvec2_new(0, 0),
			get_ray_dir(context.physic, current_section.end)
		).ratios;
		*/
		render.sections[render.nsections] = current_section;
		++render.nsections;
	}
	return (render);
}

t_render		build_sections_portals(t_game game, t_context context,
t_render render)
{
	int	i;

	i = 0;
	render.nportals = 0;
	while (i < render.nsections)
	{
		if (render.sections[i].wall.portal >= 0)
		{
			render.portals[render.nportals] = render.sections[i];
			++render.nportals;
		}
		++i;
	}
	return (render);
}

/*********************************************************************************
*********************************************************************************/

/*********************************************************************************
 * PROJECTION
*********************************************************************************/

t_wall_proj_tmp	wall_projection(int id, t_hit hit, t_context context, t_section section)
{
	t_wall_proj_tmp res;
	t_fvec2		h;
	const int	span = section.end - section.start;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.ceiling);
	res.mat_ceiling = *context.sector.ceiling_mat;
	res.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.bot = f_to_int(f_div(RATIO * h.u, hit.ratios.v) + (f_from_int(2) + context.physic.look_v) * 100);
	res.top = f_to_int(f_div(RATIO * h.v, hit.ratios.v) + (f_from_int(2) + context.physic.look_v) * 100);
	res.id = id;
	res.u = hit.ratios.u;
	res.sector = context.sector;
	return (res);
}

t_portal_proj	portal_projection(int id, t_hit hit, t_context context, t_section section)
{
	t_portal_proj	res;
	t_fvec2			h;
	t_fvec2			h2;
	const int		span = section.end - section.start;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.ceiling);
	h2.u = f_from_float((context.physic.pos.z + context.physic.height) - section.next.floor);
	h2.v = f_from_float((context.physic.pos.z + context.physic.height) - section.next.ceiling);
	res.mat_ceiling = *context.sector.ceiling_mat;
	res.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.bot = f_to_int(f_div(RATIO * h.u, hit.ratios.v) + (f_from_int(2) + context.physic.look_v) * 100);
	res.top = f_to_int(f_div(RATIO * h.v, hit.ratios.v) + (f_from_int(2) + context.physic.look_v) * 100);
	res.step = res.bot + f_to_int(f_div(RATIO * (h2.u - h.u), hit.ratios.v));
	res.ceil = res.top + f_to_int(f_div(RATIO * (h2.v - h.v), hit.ratios.v));
	res.id = id;
	res.u = hit.ratios.u;
	res.sector = context.sector;
	return (res);
}

/*********************************************************************************
*********************************************************************************/

/*********************************************************************************
 * RENDERING
*********************************************************************************/

void	draw_wall(int id, t_wall_proj_tmp proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int	i;

	i = 0;
	while (i < proj.top && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = BLUE;
		++i;
	}
	while (i < proj.bot & i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = RED;
		++i;
	}
	while (i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = GREEN;
		++i;
	}
}

void	draw_portal(int id, t_portal_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = 0;
	while (i < proj.top && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = BLUE;
		++i;
	}
	while (i < proj.ceil && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = RED;
		++i;
	}
	i = (proj.step >= 0) ? proj.step : 0;
	while (i < proj.bot && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = RED;
		++i;
	}
	while (i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = GREEN;
		++i;
	}
}

void	render_wall_tmp(t_context context, t_section section, t_color *buf,
u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_wall_proj_tmp	proj;

	id = section.start;
	while (id <= section.end)
	{
		hit = ray_seg(
			take_left(section.wall.a, section.wall.b),
			take_right(section.wall.a, section.wall.b),
			fvec2_new(0, 0),
			get_ray_dir(context.physic, id)
		);
		proj = wall_projection(id - section.start - 1, hit, context, section);
		draw_wall(id, proj, buf, ids);
		++id;
	}
}

void	render_portal(t_context context, t_section section, t_color *buf,
u_int32_t *ids)
{
	int				id;
	t_hit			hit;
	t_portal_proj	proj;

	id = section.start;
	while (id < section.end)
	{
		hit = ray_seg(
			take_left(section.wall.a, section.wall.b),
			take_right(section.wall.a, section.wall.b),
			fvec2_new(0, 0),
			get_ray_dir(context.physic, id)
		);
		proj = portal_projection(id - section.start, hit, context, section);
		draw_portal(id, proj, buf, ids);
		++id;
	}
}

/*********************************************************************************
*********************************************************************************/

t_sector	teleport_sector(t_game game, t_context context, t_section section)
{
	t_sector	next;

	if (game.portals[section.wall.portal].from_sector == context.sector.sector_id)
		next = game.sectors[game.portals[section.wall.portal].to_sector];
	else
		next = game.sectors[game.portals[section.wall.portal].from_sector];
	return (next);
}

t_context	teleport(t_game game, t_context context, t_section section)
{
	t_wall			to_wall;
	t_wall			from_wall;
	const t_portal	portal = game.portals[section.wall.portal];

	context.left = section.start;
	context.right = section.end;
	if (portal.from_sector == context.sector.sector_id)
	{
		context.sector = game.sectors[portal.to_sector];
		context.mask = portal.to_wall;
		from_wall = game.walls[portal.from_wall];
		to_wall = game.walls[portal.to_wall];
	}
	else
	{
		context.sector = game.sectors[portal.from_sector];
		context.mask = portal.from_wall;
		from_wall = game.walls[portal.to_wall];
		to_wall = game.walls[portal.from_wall];
	}
	context.physic.pos.x += game.points[to_wall.a].u - game.points[from_wall.a].u;
	context.physic.pos.y += game.points[to_wall.a].v - game.points[from_wall.a].v;
	return (context);
}

void	render(t_game game, t_context context, t_color *buf, u_int32_t *id_buf)
{
	const t_limit	limit_rays = build_limits(context);
	const t_bunch	bunch = build_bunch(game, context, limit_rays);
	t_render		r;
	t_section		current;
	int				i;
	
	i = 0;
	r = build_sections(context, bunch, limit_rays);
	r = build_sections_portals(game, context, r);
	while (i < r.nsections)
	{
		current = r.sections[i];
		if (context.mask == -1)
			printf("%d -> %d, ", current.start, current.end);
		if (current.wall.portal == -1)
			render_wall_tmp(context, current, buf, id_buf);
		else
		{
			current.next = teleport_sector(game, context, current);
			render_portal(context, current, buf, id_buf);
		}
		++i;
	}
	if (context.mask == -1)
		printf("\n");
	i = 0;
	while (i < r.nportals)
	{
		context = teleport(game, context, r.portals[i]);
		render(game, context, buf, id_buf);
		++i;
	}
}
