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
{ t_limit		limit_rays;

	limit_rays.left.dir = get_ray_dir(context.physic, context.left);
	limit_rays.left.id = context.left;
	limit_rays.right.dir = get_ray_dir(context.physic, context.right);
	limit_rays.left.id = context.right;
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
	const t_sector	sector = game.sectors[context.sector];
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
		id = f_to_int(col.ratios.v * (context.right - context.left));
	printf("ray id: %d\n", id);
	return (id);
}

t_render		build_sections(t_game game, t_context context, t_bunch bunch,
t_limit limits)
{
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	t_cache_wall	current;
	t_section		current_section;
	t_render		render;

	render.nsections = 0;
	//while (render.nsections < bunch.nwalls)
	//{
		current = bunch.walls[render.nsections];
		current_section.wall = current;
		printf("wall id: %zu\n", current.id);
		current_section.start = get_ray_id(take_left(current.a, current.b), limits, context, context.left);
		//current_section.end = get_ray_id(pos, take_right(current.a, current.b), limits, limits.i_right);
		current_section.a = ray_seg(
			take_left(current.a, current.b),
			take_right(current.a, current.b),
			fvec2_new(0, 0),
			get_ray_dir(context.physic, current_section.start)
		).ratios;
		printf("	left: (%f, %f)\n", f_to_float(current_section.a.u), f_to_float(current_section.a.v));
		printf("	ray: (%f, %f)\n",
			f_to_float(get_ray_dir(context.physic, current_section.start).u),
			f_to_float(get_ray_dir(context.physic, current_section.start).v)
		);
		++render.nsections;
	//}
}

/*********************************************************************************
*********************************************************************************/

void	render(t_game game, t_context context, t_color *buf, u_int32_t *id_buf)
{
	printf("%f\n", game.player.physic.look_h);
	const t_limit	limit_rays = build_limits(context);
	const t_bunch	bunch = build_bunch(game, context, limit_rays);
	build_sections(game, context, bunch, limit_rays);
}
