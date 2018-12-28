/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:34:10 by iporsenn          #+#    #+#             */
/*   Updated: 2018/12/28 18:14:21 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


static void		draw_horizon(float *coord, int *diff, int *inc, t_color *buff)
{
	int		i;
	int		cumul;

	cumul = diff[1] / 2;
	i = -1;
	while (++i < diff[1])
	{
		coord[1] += inc[1];
		cumul += diff[0];
		if (cumul >= diff[1])
		{
			cumul -= diff[1];
			coord[0] += inc[0];
		}
		if ((coord[1] > 0 && coord[1] < HEIGHT) && (coord[0] > 0 && coord[0] < \
					WIDTH))
			buff[(int)coord[0] + (int)coord[1] * WIDTH] = (t_color){255, 255, 255, 255};
	}
}

static void		draw_vertical(float *coord, int *diff, int *inc, t_color *buff)
{
	int i;
	int cumul;

	cumul = diff[0] / 2;
	i = -1;
	while (++i < diff[0])
	{
		coord[0] += inc[0];
		cumul += diff[1];
		if (cumul >= diff[0])
		{
			cumul -= diff[0];
			coord[1] += inc[1];
		}
		if ((coord[1] > 0 && coord[1] < HEIGHT) && (coord[0] > 0 && coord[0] < \
					WIDTH))
			buff[(int)coord[0] + (int)coord[1] * WIDTH] = (t_color){255, 255, 255, 255};
	}
}

void			bresenham(float *coord_src, float *coord_dst, t_color *buff)
{
	int diff[2];
	int inc[2];

	diff[0] = coord_dst[0] - coord_src[0];
	diff[1] = coord_dst[1] - coord_src[1];
	inc[0] = (diff[0] > 0) ? 1 : -1;
	inc[1] = (diff[1] > 0) ? 1 : -1;
	diff[0] = abs(diff[0]);
	diff[1] = abs(diff[1]);
	if ((coord_src[1] > 0 && coord_src[1] < WIDTH) && (coord_src[0] > 0 && \
				coord_src[0] < HEIGHT))
		buff[(int)coord_src[1] + (int)coord_src[0] * WIDTH] = (t_color){255, 255, 255, 255};
	if (diff[1] > diff[0])
		draw_horizon(coord_src, diff, inc, buff);
	else
		draw_vertical(coord_src, diff, inc, buff);
}
