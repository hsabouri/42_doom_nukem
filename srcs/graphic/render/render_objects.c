/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:33:45 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/17 11:50:44 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "../sort.h"

void	sections_entities(t_render render, const t_context context,
t_color *buf, u_int32_t *id_buf)
{
	t_section_entity	current;
	int					i;

	i = 0;
	render = sort_entities(render);
	while (i < render.nentities)
	{
		current = render.entities[i];
		render_entity(context, current, buf, id_buf);
		++i;
	}
}

void	render_wall(const t_context context, const t_section section,
t_color *buf, u_int32_t *ids)
{
	int		id;
	t_hit	hit;
	t_proj	proj;

	id = section.start;
	while (id <= section.end && id != context.right)
	{
		hit = ray_seg(
		take_left(section.wall.a, section.wall.b),
		take_right(section.wall.a, section.wall.b),
		fvec2_new(0, 0),
		get_ray_dir(context.physic, id));
		if (hit.ratios.v < 10)
			hit.ratios.v = 10;
		proj = wall_projection(id, hit, context, section);
		draw_wall(id, proj, buf, ids);
		++id;
	}
}

void	render_portal(const t_context context, const t_section section,
t_color *buf, u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_proj		proj;

	id = section.start;
	while (id < section.end && id != context.right)
	{
		hit = ray_seg(
		take_left(section.wall.a, section.wall.b),
		take_right(section.wall.a, section.wall.b),
		fvec2_new(0, 0),
		get_ray_dir(context.physic, id - 1));
		if (hit.ratios.v < 10)
			hit.ratios.v = 10;
		proj = portal_projection(id, hit, context, section);
		draw_portal(id, proj, buf, ids);
		++id;
	}
}

void	render_entity(const t_context context, const t_section_entity section,
t_color *buf, u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_e_proj	proj;

	id = section.start;
	while (id < section.end && id != context.right)
	{
		hit = ray_seg(section.entity.a, section.entity.b,
			fvec2_new(0, 0), get_ray_dir(context.physic, id));
		if (hit.ratios.v < 10)
			hit.ratios.v = 10;
		proj = entity_projection(hit, context, section);
		proj.u = hit.ratios.u;
		proj.x = hit.ratios.u;
		proj.tex.ambient = context.sector.ambient;
		draw_entity(id, proj, buf, ids);
		++id;
	}
}
