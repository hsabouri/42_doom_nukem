/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_polygon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/19 16:47:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

/*
 *	Every point is considered connected to the preceeding one like this :
 * 		 a -----> b
 *      /          \
 *     /            \
 *    d <----------- c
 * Giving :
 * 	a -> b -> c -> d
 */

typedef struct	s_order
{
	int	left[2];
	int	right[2];
}				t_order;

#define A highest
#define B ((highest + 1) % 4)
#define C ((highest + 2) % 4)
#define D ((highest + 3) % 4)

static t_pix_fixed	from_pix(t_pix pixel)
{
	return ((t_pix_fixed) {f_from_int(pixel.x), f_from_int(pixel.y)});
}

void			quad_fill(t_color *buf, t_order order,\
t_pix_fixed *points, t_color color)
{
	const t_fixed	start = MAX(points[order.left[0]].y, points[order.right[0]].y);
	const t_fixed	end = MIN(points[order.left[1]].y, points[order.right[1]].y);
	t_fixed			i;
	t_fixed			a;
	t_fixed			b;
	t_fixed			coef;

	i = start;
	while (i <= end)
	{
		coef = f_div(i - points[order.left[0]].y, points[order.left[1]].y - points[order.left[0]].y);
		a = f_mul(coef, points[order.left[1]].x - points[order.left[0]].x ) + points[order.left[0]].x;
		coef = f_div(i - points[order.right[0]].y, points[order.right[1]].y - points[order.right[0]].y);
		b = f_mul(coef, points[order.right[1]].x - points[order.right[0]].x) + points[order.right[0]].x;
		while ((a >= 0 || !(a = 0)) && a < f_from_int(WIDTH) && a < b)
		{
			buf[f_to_int(a) + f_to_int(i) * WIDTH] = color;
			a = f_add_int(a, 1);
		}
		i = f_add_int(i, 1);
	}
}

void				quad(t_color *buf, t_pix pixes[4], t_color color)
{
	t_order		order[3];
	t_pix_fixed	points[4];
	int			highest;
	int			i;

	i = 0;
	highest = 0;
	points[0] = from_pix(pixes[0]);
	points[1] = from_pix(pixes[1]);
	points[2] = from_pix(pixes[2]);
	points[3] = from_pix(pixes[3]);
	while (++i < 4)
		if (points[i].y < points[highest].y)
			highest = i;
	order[0].left[0] = A;
	order[0].left[1] = D;
	order[0].right[0] = A;
	order[0].right[1] = B;
	if (points[B].y < points[D].y)
	{
		ft_memmove(order[1].left, order[0].left, sizeof(int) * 2);
		order[1].right[0] = B;
		order[1].right[1] = C;
	}
	else
	{
		ft_memmove(order[1].right, order[0].right, sizeof(int) * 2);
		order[1].left[0] = D;
		order[1].left[1] = C;
	}
	if (points[order[1].left[1]].y > points[order[1].right[1]].y)
	{
		ft_memmove(order[2].left, order[1].left, sizeof(int) * 2);
		order[2].right[0] = order[1].right[1];
		order[2].right[1] = (order[2].right[0] + 1) % 4;
	}
	else
	{
		ft_memmove(order[2].right, order[1].right, sizeof(int) * 2);
		order[2].left[0] = order[1].left[1];
		order[2].left[1] = (order[2].left[0] - 1) % 4;
	}
	/*
	printf("Order:\n	(%d -> %d) ===> (%d -> %d)\n	(%d -> %d) ===> (%d -> %d)\n	(%d -> %d) ===> (%d -> %d)\n",
		order[0].left[0], order[0].left[1], order[0].right[0], order[0].right[1],
		order[1].left[0], order[1].left[1], order[1].right[0], order[1].right[1],
		order[2].left[0], order[2].left[1], order[2].right[0], order[2].right[1]
	);
	*/
	i = 0;
	while (i < 3)
	{
		quad_fill(buf, order[i], points, color);
		i++;
	}
}
