/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:34:10 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/06 15:44:34 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static void		draw_horizon(t_bres bres, t_color *buff, t_color color,
int dot)
{
	int		i;
	int		cumul;

	cumul = bres.diff[1] >> 1;
	i = -1;
	while (++i < bres.diff[1])
	{
		bres.src.y += f_from_int(bres.inc[1]);
		cumul += bres.diff[0];
		if (cumul >= bres.diff[1])
		{
			cumul -= bres.diff[1];
			bres.src.x += f_from_int(bres.inc[0]);
		}
		if (bres.src.y > 0 && f_to_int(bres.src.y) < HEIGHT
		&& bres.src.x > 0 && f_to_int(bres.src.x) < WIDTH && (i / 2) % dot == 0)
			buff[f_to_int(bres.src.x) + f_to_int(bres.src.y) * WIDTH] = color;
	}
}

static void		draw_vertical(t_bres bres, t_color *buff, t_color color,
int dot)
{
	int		i;
	int		cumul;

	cumul = bres.diff[0] >> 1;
	i = -1;
	while (++i < bres.diff[0])
	{
		bres.src.x += f_from_int(bres.inc[0]);
		cumul += bres.diff[1];
		if (cumul >= bres.diff[0])
		{
			cumul -= bres.diff[0];
			bres.src.y += f_from_int(bres.inc[1]);
		}
		if (bres.src.y > 0 && f_to_int(bres.src.y) < HEIGHT
		&& bres.src.x > 0 && f_to_int(bres.src.x) < WIDTH && (i / 2) % dot == 0)
			buff[f_to_int(bres.src.x) + f_to_int(bres.src.y) * WIDTH] = color;
	}
}

void			bresenham(t_color *buff, t_pix a, t_pix b, t_color color)
{
	t_bres		bres;
	t_pix_fixed	dst;

	bres.src.x = f_from_int(a.x);
	bres.src.y = f_from_int(a.y);
	dst.x = f_from_int(b.x);
	dst.y = f_from_int(b.y);
	bres.diff[0] = b.x - a.x;
	bres.diff[1] = b.y - a.y;
	bres.inc[0] = (bres.diff[0] > 0) ? 1 : -1;
	bres.inc[1] = (bres.diff[1] > 0) ? 1 : -1;
	bres.diff[0] = abs(bres.diff[0]);
	bres.diff[1] = abs(bres.diff[1]);
	if (bres.diff[1] > bres.diff[0])
		draw_horizon(bres, buff, color, 1);
	else
		draw_vertical(bres, buff, color, 1);
}

void			dotted(t_color *buff, t_pix a, t_pix b, t_color color)
{
	t_bres		bres;
	t_pix_fixed	dst;

	bres.src.x = f_from_int(a.x);
	bres.src.y = f_from_int(a.y);
	dst.x = f_from_int(b.x);
	dst.y = f_from_int(b.y);
	bres.diff[0] = b.x - a.x;
	bres.diff[1] = b.y - a.y;
	bres.inc[0] = (bres.diff[0] > 0) ? 1 : -1;
	bres.inc[1] = (bres.diff[1] > 0) ? 1 : -1;
	bres.diff[0] = abs(bres.diff[0]);
	bres.diff[1] = abs(bres.diff[1]);
	if (bres.diff[1] > bres.diff[0])
		draw_horizon(bres, buff, color, 4);
	else
		draw_vertical(bres, buff, color, 4);
}
