/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:23:25 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 17:18:50 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

t_fvec2		get_ray_dir(t_ph physic, int id)
{
	return (vec2_to_fvec2(vec2_rot((t_vec2) {
		(-PWIDTH / 2) + (id) * (PWIDTH / WIDTH), PDIS},
		physic.look_h)));
}

t_limit		build_limits(t_context context)
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

t_hit		ray_seg(t_fvec2 a, t_fvec2 b, t_fvec2 c, t_fvec2 d)
{
	const t_fvec2	p = fvec2_sub(b, a);
	const t_fvec2	q = fvec2_sub(d, c);
	t_fvec2			ratios;
	const t_fixed	denom = fvec2_cross(p, q).z;

	if (denom == 0)
		return ((t_hit) {0, d, fvec2_new(0, 0)});
	ratios.u = -f_div(f_mul(a.u, q.v) - f_mul(c.u, q.v)
		- f_mul(q.u, a.v) + f_mul(c.v, q.u), denom);
	ratios.v = -f_div(-f_mul(a.v, p.u) + f_mul(c.v, p.u)
		+ f_mul(p.v, a.u) - f_mul(c.u, p.v), denom);
	return ((t_hit) {1, d, ratios});
}

int			get_ray_id(t_fvec2 point, t_limit limit, t_context context, int max)
{
	t_hit	col;
	int		id;

	col = ray_seg(fvec2_new(0, 0), point, limit.left.dir, limit.right.dir);
	if (col.ratios.v < 0 || col.ratios.v > f_from_int(1) || col.ratios.u < 0)
		id = max;
	else
		id = context.left + f_to_int(col.ratios.v
			* (context.right - context.left));
	return (id);
}

int			is_in_limit(t_limit limit, t_fvec2 a, t_fvec2 b)
{
	t_fvec2			r_l;
	t_fvec2			r_r;
	const t_fvec2	left = limit.left.dir;
	const t_fvec2	right = limit.right.dir;

	if ((is_left(limit.left.dir, a) && !is_left(right, b))
	|| (is_left(left, b) && !is_left(right, a)))
	{
		r_l = ray_seg(a, b, fvec2_new(0, 0), left).ratios;
		r_r = ray_seg(a, b, fvec2_new(0, 0), right).ratios;
		if (r_l.v > 0 && r_r.v > 0)
			return (1);
		return (0);
	}
	else if (!((is_left(left, a) && is_left(left, b))
	|| (!is_left(right, a) && !is_left(right, b))))
		return (1);
	return (0);
}
