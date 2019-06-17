/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:49:30 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/17 11:49:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "../sort.h"

static t_render	render_sector(const t_game game, t_context context,
t_color *buf, u_int32_t *id_buf)
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
	free(bunch.entities);
	free(bunch.walls);
	return (r);
}

void			render(const t_game game, t_context context, t_color *buf,
u_int32_t *id_buf)
{
	t_render		r;
	int				i;

	if (context.stack_id >= 30)
		return ;
	context.stack_id++;
	r = render_sector(game, context, buf, id_buf);
	free(r.entities);
	free(r.sections);
	i = 0;
	while (i < r.nportals)
	{
		render(game, teleport(game, context, r.portals[i]), buf, id_buf);
		++i;
	}
	free(r.portals);
}
