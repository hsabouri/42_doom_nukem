/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:49:30 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/05 15:59:18 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

void	render_wall(t_context context, t_section section, t_color *buf,
u_int32_t *ids)
{
	int		id;
	t_hit	hit;
	t_proj	proj;

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
	int			id;
	t_hit		hit;
	t_proj		proj;

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

void	render_entity(t_context context, t_section_entity section, t_color *buf,
u_int32_t *ids)
{
	int			id;
	t_hit		hit;
	t_e_proj	proj;
	const int	span = (section.end - section.start);

	id = section.start;
	while (id < section.end)
	{
		hit = ray_seg(section.entity.a, section.entity.b,
			fvec2_new(0, 0), get_ray_dir(context.physic, id));
		proj = entity_projection(id - section.start, hit, context, section);
		draw_entity(id, proj, buf, ids);
		++id;
	}
}

void	sections_entities(t_render render, t_context context, t_color *buf,
u_int32_t *id_buf)
{
	t_section_entity	current;
	int					i;

	i = 0;
	while (i < render.nentities)
	{
		current = render.entities[i];
		render_entity(context, current, buf, id_buf);
		++i;
	}
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
