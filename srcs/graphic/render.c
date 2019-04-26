/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:49:30 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/18 14:54:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./sort.h"

void	render_wall(const t_context context, const t_section section, t_color *buf,
u_int32_t *ids)
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
			get_ray_dir(context.physic, id)
		);
		proj = wall_projection(id, hit, context, section);
		draw_wall(id, proj, buf, ids);
		++id;
	}
}

void	render_portal(const t_context context, const t_section section, t_color *buf,
u_int32_t *ids)
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
			get_ray_dir(context.physic, id - 1)
		);
		proj = portal_projection(id, hit, context, section);
		draw_portal(id, proj, buf, ids);
		++id;
	}
}

void	render_entity(const t_context context, const t_section_entity section, t_color *buf,
u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_e_proj	proj;

	id = section.start;
	while (id < section.end && id != context.right)
	{
		hit = ray_seg(section.entity.a, section.entity.b,
			fvec2_new(0, 0), get_ray_dir(context.physic, id));
		proj = entity_projection(hit, context, section);
		draw_entity(id, proj, buf, ids);
		++id;
	}
}

void	sections_entities(t_render render, const t_context context, t_color *buf,
u_int32_t *id_buf)
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

void	render(const t_game game, const t_context context, t_color *buf, u_int32_t *id_buf)
{
	const t_limit	limit_rays = build_limits(context);
	const t_bunch	bunch = build_bunch(game, context, limit_rays);
	t_render		r;
	t_section		current;
	int				i;
	
	i = 0;
	r = build_sections(context, bunch, limit_rays);
	r = build_sections_portals(r);
	sections_entities(r, context, buf, id_buf);
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
