/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_portal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 17:42:27 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 17:57:42 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static int	draw_ceiling(int id, t_proj proj, t_color *buf, int i)
{
	while (i < proj.ceil && i < HEIGHT)
	{
		if (buf[i * WIDTH + id].a == 0)
		{
			buf[i * WIDTH + id] = get_wall_pixel(proj, i);
			proj.ids[i * WIDTH + id] = proj.uid_ceil;
		}
		++i;
	}
	return (i);
}

static void	draw_step(int id, t_proj proj, t_color *buf, int i)
{
	if (proj.step < proj.bot)
	{
		i = (proj.step >= 0) ? proj.step : 0;
		while (i < proj.bot && i < HEIGHT)
		{
			if (buf[i * WIDTH + id].a == 0)
			{
				buf[i * WIDTH + id] = get_wall_pixel(proj, i);
				proj.ids[i * WIDTH + id] = proj.uid_step;
			}
			++i;
		}
	}
}

void		draw_portal(int id, t_proj proj, t_color *buf, u_int32_t *ids)
{
	int	i;

	proj.ids = ids;
	i = draw_roof(id, proj, buf, ids);
	draw_floor(id, proj, buf, ids);
	i = draw_ceiling(id, proj, buf, i);
	if (proj.is_portal_tex)
		while (i < proj.step && i < proj.bot && i < HEIGHT)
		{
			if (buf[i * WIDTH + id].a == 0)
			{
				buf[i * WIDTH + id] = get_portal_pixel(proj, i);
				proj.ids[i * WIDTH + id] = proj.uid;
			}
			++i;
		}
	draw_step(id, proj, buf, i);
}
