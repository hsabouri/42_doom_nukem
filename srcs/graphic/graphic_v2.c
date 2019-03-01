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

void	print_fvec2(t_fvec2 vec)
{
	printf("(%f, %f)\n", f_to_float(vec.u), f_to_float(vec.v));
}

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
		return ((t_hit) {0, d, fvec2_new(0, 0)});
	ratios.u = -f_div(f_mul(a.u, q.v) - f_mul(c.u, q.v) -
		f_mul(q.u, a.v) + f_mul(c.v, q.u), denom);
	ratios.v = -f_div(-f_mul(a.v, p.u) + f_mul(c.v, p.u) +
		f_mul(p.v, a.u) - f_mul(c.u, p.v), denom);
	return ((t_hit) {1, d, ratios});
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

/*********************************************************************************
 * BUNCH CALCULATION
*********************************************************************************/

static inline int		is_in_limit(t_limit limit, t_context context,
t_fvec2 a, t_fvec2 b, int id)
{
	t_fvec2			r_l;
	t_fvec2			r_r;
	const t_fvec2	left = limit.left.dir;
	const t_fvec2	right = limit.right.dir;

	if ((is_left(limit.left.dir, a) && !is_left(right, b)) ||
		(is_left(left, b) && !is_left(right, a)))
	{
		r_l = ray_seg(a, b, fvec2_new(0, 0), left).ratios;
		r_r = ray_seg(a, b, fvec2_new(0, 0), right).ratios;
		if (r_l.v > 0 && r_r.v > 0)
			return (1);
		return (0);
	}
	else if (!((is_left(left, a) && is_left(left, b)) ||
		(!is_left(right, a) && !is_left(right, b))))
		return (1);
	return (0);
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
			is_in_limit(limit, context, current.a, current.b, i))
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

t_wall_proj	wall_projection(int id, t_hit hit, t_context context, t_section section)
{
	t_wall_proj res;
	t_fvec2		h;
	int			span;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.ceiling);
	res.plane.mat_ceiling = *context.sector.ceiling_mat;
	res.plane.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) + context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) + context.physic.look_v * 100);
	res.id = id;
	res.u = hit.ratios.u;
	res.x = hit.ratios.u;
	span = res.bot - res.top;
	res.y_iter = f_from_int(1 << 8) / (span + !span);
	res.tex.ambient = context.sector.ambient;
	res.plane.h = h;
	res.plane.pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	res.plane.ray = hit.ray;
	res.plane.wr.u = f_div(-h.v, f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH)));
	res.plane.wr.v = f_div(-h.u, f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH)));
	res.plane.look_v = f_to_int(context.physic.look_v * 100);
	return (res);
}

t_portal_proj	portal_projection(int id, t_hit hit, t_context context, t_section section)
{
	t_portal_proj	res;
	t_fvec2			h;
	t_fvec2			h2;
	int				span;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) - context.sector.ceiling);
	h2.u = f_from_float((context.physic.pos.z + context.physic.height) - section.next.floor);
	h2.v = f_from_float((context.physic.pos.z + context.physic.height) - section.next.ceiling);
	res.plane.mat_ceiling = *context.sector.ceiling_mat;
	res.plane.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) + context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) + context.physic.look_v * 100);
	res.step = res.bot + f_to_int(f_div(RATIO * (h2.u - h.u), hit.ratios.v));
	res.ceil = res.top + f_to_int(f_div(RATIO * (h2.v - h.v), hit.ratios.v));
	res.id = id;
	res.u = hit.ratios.u;
	res.x = hit.ratios.u;
	span = res.bot - res.top;
	res.y_iter = f_from_int(1 << 8) / (span + !span);
	res.tex.ambient = context.sector.ambient;
	res.plane.h = h;
	res.plane.pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	res.plane.ray = hit.ray;
	res.plane.wr.u = f_div(-h.v, f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH)));
	res.plane.wr.v = f_div(-h.u, f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH)));
	res.plane.look_v = f_to_int(context.physic.look_v * 100);
	return (res);
}

/*********************************************************************************
*********************************************************************************/

/*********************************************************************************
 * RENDERING
*********************************************************************************/

static t_color	color_filter(t_color a, t_color filter)
{
	return ((t_color) {
		.a = (a.a * filter.a) >> 8,
		.b = (a.b * filter.b) >> 8,
		.g = (a.g * filter.g) >> 8,
		.r = (a.r * filter.r) >> 8,
	});
}

static t_color	color_superpose(t_color a, t_color b)
{
	if (b.a)
		return (b);
	else
		return (a);
}

t_color	get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix, char p)
{
	int		x;
	int		y;
	t_img	img;
	t_color	res;

	if (!mat.texture)
		res = mat.color;
	else
	{
		img = *mat.texture;
		x = f_to_int((f_mul(pix.u, mat.sca.u) - mat.pos.u) * img.width);
		y = f_to_int((f_mul(pix.v, mat.sca.v) - mat.pos.v) * img.height) >> p;
		if (mat.mode == TILING)
		{
			y = y % img.height;
			x = x % img.width;
		}
		if ((uint)x >= img.width || x < 0 || (uint)y >= img.height || y < 0)
			res = mat.color;
		else
			res = color_filter(img.content[x + y * img.width], mat.filter);
	}
	if (mat.overlay)
		res = color_superpose(res, get_mat_pixel(*mat.overlay, tex, pix, p));
	return (color_filter(res, tex.ambient));
}

t_color	get_wall_pixel(t_wall_proj proj, int y)
{
	t_fvec2 pix;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top);
	return (get_mat_pixel(proj.mat_wall, proj.tex, pix, 8));
}

t_color	get_roof_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fixed	z;
	t_fvec2	pix;

	z = f_from_int(HEIGHT / 2 - y + proj.look_v) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray, f_div(proj.wr.u, z));
	pix = fvec2_add(pix, proj.pos);
	return (get_mat_pixel(proj.mat_ceiling, tex, pix, 0));
}

t_color	get_floor_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fixed	z;
	t_fvec2	pix;

	z = f_from_int(HEIGHT / 2 - y + proj.look_v) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray, f_div(proj.wr.v, z));
	pix = fvec2_add(pix, proj.pos);
	return (get_mat_pixel(proj.mat_floor, tex, pix, 0));
}

void	draw_wall(int id, t_wall_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = 0;
	while (i < proj.top && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = get_roof_pixel(proj.plane, proj.tex, i);
		++i;
	}
	while (i < proj.bot & i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = get_wall_pixel(proj, i);
		++i;
	}
	while (i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = get_floor_pixel(proj.plane, proj.tex, i);
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
			buf[i * WIDTH + id] = get_roof_pixel(proj.plane, proj.tex, i);
		++i;
	}
	while (i < proj.ceil && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = RED;
		++i;
	}
	if (proj.step < proj.bot)
	{
		i = (proj.step >= 0) ? proj.step : 0;
		while (i < proj.bot && i < HEIGHT)
		{
			if (verif[i * WIDTH + id] == 0)
				buf[i * WIDTH + id] = RED;
			++i;
		}
	}
	else
		i = (proj.bot >= 0) ? proj.bot : 0;
	while (i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
			buf[i * WIDTH + id] = get_floor_pixel(proj.plane, proj.tex, i);
		++i;
	}
}

void	render_wall(t_context context, t_section section, t_color *buf,
u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_wall_proj	proj;

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
		if (current.wall.portal == -1)
			render_wall(context, current, buf, id_buf);
		else
		{
			current.next = teleport_sector(game, context, current);
			render_portal(context, current, buf, id_buf);
		}
		++i;
	}
	i = 0;
	while (i < r.nportals)
	{
		render(game, teleport(game, context, r.portals[i]), buf, id_buf);
		++i;
	}
}
