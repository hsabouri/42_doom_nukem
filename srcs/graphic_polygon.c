/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_polygon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/19 18:24:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

/*
**	Recalls:
**	 -	coef = (y - by) / (ay - by)
**	 -	newx = coef * (bx - ax) + ax
*/

static void			part_fill(t_color *buf, t_order order,\
t_pix_fixed *pts, t_color color)
{
	const t_fixed	end = MIN(pts[order.left[1]].y, pts[order.right[1]].y);
	t_fixed			start;
	t_fixed			a;
	t_fixed			b;
	t_fixed			coef;

	start = MAX(pts[order.left[0]].y, pts[order.right[0]].y);
	while (start <= end)
	{
		coef = f_div(start - pts[order.left[0]].y,
		pts[order.left[1]].y - pts[order.left[0]].y);
		a = f_mul(coef, pts[order.left[1]].x - pts[order.left[0]].x) +
		pts[order.left[0]].x;
		coef = f_div(start - pts[order.right[0]].y,
		pts[order.right[1]].y - pts[order.right[0]].y);
		b = f_mul(coef, pts[order.right[1]].x - pts[order.right[0]].x) +
		pts[order.right[0]].x;
		while ((a >= 0 || !(a = 0)) && a < f_from_int(WIDTH) && a < b)
		{
			buf[f_to_int(a) + f_to_int(start) * WIDTH] = color;
			a = f_add_int(a, 1);
		}
		start = f_add_int(start, 1);
	}
}

static void			quad_order(int highest, t_order *ord, t_pix_fixed pts[4])
{
	if (pts[B].y < pts[D].y)
	{
		ft_memmove(ord[1].left, ord[0].left, sizeof(int) * 2);
		ord[1].right[0] = B;
		ord[1].right[1] = C;
	}
	else
	{
		ft_memmove(ord[1].right, ord[0].right, sizeof(int) * 2);
		ord[1].left[0] = D;
		ord[1].left[1] = C;
	}
	if (pts[ord[1].left[1]].y > pts[ord[1].right[1]].y)
	{
		ft_memmove(ord[2].left, ord[1].left, sizeof(int) * 2);
		ord[2].right[0] = ord[1].right[1];
		ord[2].right[1] = (ord[2].right[0] + 1) % 4;
	}
	else
	{
		ft_memmove(ord[2].right, ord[1].right, sizeof(int) * 2);
		ord[2].left[0] = ord[1].left[1];
		ord[2].left[1] = (ord[2].left[0] - 1) % 4;
	}
}

void				quad(t_color *buf, t_pix pixes[4], t_color color)
{
	t_order		order[3];
	t_pix_fixed	points[4];
	int			highest;
	int			i;

	i = -1;
	highest = 0;
	while (++i < 4)
		points[i] = from_pix(pixes[i]);
	i = 0;
	while (++i < 4)
		if (points[i].y < points[highest].y)
			highest = i;
	order[0].left[0] = A;
	order[0].left[1] = D;
	order[0].right[0] = A;
	order[0].right[1] = B;
	quad_order(highest, order, points);
	i = -1;
	while (++i < 3)
		part_fill(buf, order[i], points, color);
}
