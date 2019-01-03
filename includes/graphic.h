/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:27:41 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/03 16:43:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

/*
** This header contains all the structures used to draw on screen in a
** highly optimized manner.
*/

# include <structure.h>

# define WIDTH 640
# define HEIGHT 480
# define RATIO WIDTH / 2

typedef struct		s_color
{
	u_int8_t	b;
	u_int8_t	g;
	u_int8_t	r;
	u_int8_t	a;
}					t_color;

# define WHITE		(t_color){255,255,255,255}
# define RED		(t_color){255,0,0,255}
# define GREEN		(t_color){0,255,0,255}
# define BLUE		(t_color){0,0,255,255}
# define BLACK		(t_color){0,0,0,255}
# define NO_COLOR	(t_color){0,0,0,0}

typedef struct		s_pix
{
	int32_t	x;
	int32_t	y;
}					t_pix;

typedef struct		s_pix_fixed
{
	t_fixed	x;
	t_fixed	y;
}					t_pix_fixed;

typedef struct		s_order
{
	int	left[2];
	int	right[2];
}					t_order;

typedef struct		s_bres
{
	t_pix_fixed	src;
	int			diff[2];
	int			inc[2];
}					t_bres;

/*
# define A highest
# define B ((highest + 1) % 4)
# define C ((highest + 2) % 4)
# define D ((highest + 3) % 4)
*/

/*
** Faster modulo
**	n % m == n & (m - 1)
** where m is a power of 2
** 10x faster and works with negative values of n (% can not)
*/

# define A highest
# define B ((highest + 1) & 3)
# define C ((highest + 2) & 3)
# define D ((highest + 3) & 3)

void				quad(t_color *buf, t_pix_fixed points[4], t_color color);
t_pix_fixed			from_pix(t_pix pixel);

void				display_sector(t_sector sector, t_game game, t_color *buf);

void				bresenham(t_color *buff, t_pix a, t_pix b, \
					t_color color);

#endif
