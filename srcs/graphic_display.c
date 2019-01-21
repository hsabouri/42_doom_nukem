/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:25:08 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/21 20:02:50 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static int		draw_roof(int x, t_proj proj, t_last last, t_color *buf)
{
	int y;

	y = last.start;
	while (y < proj.top && y < last.end)
	{
		buf[x + y * WIDTH] = get_roof_pixel(*proj.sector.ceiling_mat, proj, y);
		++y;
	}
	return (y);
}

static int		draw_step_ceiling(int x, t_proj proj, t_last last, t_color *buf)
{
	int y;
	int res;

	y = (proj.top >= last.start) ? proj.top : last.start;
	while (y < proj.ceil && y < last.end)
	{
		buf[x + y * WIDTH] = get_wall_pixel(*proj.wall.mat, proj, y);
		++y;
	}
	res = y;
	y = (proj.step >= 0) ? proj.step : 0;
	while (y < proj.bot && y < last.end)
	{
		buf[x + y * WIDTH] = get_wall_pixel(*proj.wall.mat, proj, y);
		++y;
	}
	return (res);
}

static int		draw_wall(int x, t_proj proj, t_last last, t_color *buf)
{
	int y;

	y = (proj.top >= last.start) ? proj.top : last.start;
	while (y < proj.bot && y < last.end)
	{
		buf[x + y * WIDTH] = get_wall_pixel(*proj.wall.mat, proj, y);
		++y;
	}
	return (y);
}

static int		draw_floor(int x, t_proj proj, t_last last, t_color *buf)
{
	int y;

	y = (proj.bot >= last.start) ? proj.bot : last.start;
	if (y >= last.end)
		return (last.end);
	while (y < last.end)
	{
		buf[x + y * WIDTH] = get_floor_pixel(*proj.sector.floor_mat, proj, y);
		++y;
	}
	return (y);
}

void			render_wall(int x, t_proj proj, t_color *buf, size_t frame)
{
	static t_last	last = (t_last) {0, 0, 0, HEIGHT};

	if (x != last.x || frame != last.frame)
		last = (t_last) {frame, x, 0, HEIGHT};
	last.start = draw_roof(x, proj, last, buf);
	if (proj.wall.portal == -1)
		last.start = draw_wall(x, proj, last, buf);
	else
		last.start = draw_step_ceiling(x, proj, last, buf);
	draw_floor(x, proj, last, buf);
	if (proj.is_step)
		last.end = (proj.step < last.end) ? proj.step : last.end;
	else
		last.end = (proj.bot < last.end) ? proj.bot : last.end;
}
