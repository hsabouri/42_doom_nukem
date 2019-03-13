/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:16:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/11 19:19:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static int	draw_roof(int id, t_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = 0;
	while (i < proj.top && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
		{
			buf[i * WIDTH + id] = get_roof_pixel(proj.plane, proj.plane.tex_roof, i);
			ids[i * WIDTH + id] = proj.plane.uid_roof;
		}
		++i;
	}
	return (i);
}

static void	draw_floor(int id, t_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int i;

	i = (proj.bot >= 0) ? proj.bot : 0;
	while (i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
		{
			buf[i * WIDTH + id] = get_floor_pixel(proj.plane, proj.plane.tex_floor, i);
			ids[i * WIDTH + id] = proj.plane.uid_floor;
		}
		++i;
	}
}

void		draw_wall(int id, t_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = draw_roof(id, proj, buf, ids);
	while (i < proj.bot & i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
		{
			buf[i * WIDTH + id] = get_wall_pixel(proj, i);
			ids[i * WIDTH + id] = proj.uid;
		}
		++i;
	}
	draw_floor(id, proj, buf, ids);
}

void		draw_portal(int id, t_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = draw_roof(id, proj, buf, ids);
	while (i < proj.ceil && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
		{
			buf[i * WIDTH + id] = get_wall_pixel(proj, i);
			ids[i * WIDTH + id] = proj.uid_ceil;
		}
		++i;
	}
	if (proj.is_portal_tex)
		while (i < proj.step && i < proj.bot && i < HEIGHT)
		{
			if (verif[i * WIDTH + id] == 0)
			{
				buf[i * WIDTH + id] = get_portal_pixel(proj, i);
				ids[i * WIDTH + id] = proj.uid;
			}
			++i;
		}
	if (proj.step < proj.bot)
	{
		i = (proj.step >= 0) ? proj.step : 0;
		while (i < proj.bot && i < HEIGHT)
		{
			if (verif[i * WIDTH + id] == 0)
			{
				buf[i * WIDTH + id] = get_wall_pixel(proj, i);
				ids[i * WIDTH + id] = proj.uid_step;
			}
			++i;
		}
	}
	draw_floor(id, proj, buf, ids);
}

void		draw_entity(int id, t_e_proj proj, t_color *buf, u_int32_t *ids)
{
	const u_int32_t	*verif = (u_int32_t *)buf;
	int				i;

	i = (proj.top >= 0) ? proj.top : 0;
	while (i < proj.bot && i < HEIGHT)
	{
		if (verif[i * WIDTH + id] == 0)
		{
			buf[i * WIDTH + id] = get_entity_pixel(proj, i);
			ids[i * WIDTH + id] = proj.uid;
		}
		++i;
	}
}
