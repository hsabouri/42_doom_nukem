/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:27:41 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/21 12:29:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

/*
** This header contains all the structures used to draw on screen in a
** highly optimized manner.
*/

# include <structure.h>

# define WIDTH 720
# define HEIGHT 480
# define PWIDTH	2.5
# define RATIO WIDTH / PWIDTH
# define PDIS 1.0

# define WHITE		(t_color){255,255,255,255}
# define RED		(t_color){255,0,0,255}
# define GREEN		(t_color){0,255,0,255}
# define BLUE		(t_color){0,0,255,255}
# define BLACK		(t_color){0,0,0,255}
# define NO_COLOR	(t_color){0,0,0,0}

# define UBE		(t_color){125,122,188,255}
# define LIBERTY	(t_color){100,87,166,255}
# define TRACTOR_R	(t_color){239,20,54,255}
# define RICH_BLACK	(t_color){0,20,33,255}
# define MOONSTONE	(t_color){98,190,193,255}
# define MUSTARD	(t_color){255,224,102,255}

typedef struct	s_pix
{
	int32_t	x;
	int32_t	y;
}				t_pix;

typedef struct	s_pix_fixed
{
	t_fixed	x;
	t_fixed	y;
}				t_pix_fixed;

typedef struct	s_order
{
	int	left[2];
	int	right[2];
}				t_order;

typedef struct	s_bres
{
	t_pix_fixed	src;
	int			diff[2];
	int			inc[2];
}				t_bres;

typedef struct	s_ray
{
	t_fvec2		dir;
	int			id;
	ssize_t		mask_wall;
}				t_ray;

typedef struct	s_i_wall
{
	size_t		wall_id;
	t_fvec2		a;
	t_fvec2		b;
}				t_i_wall;

typedef struct	s_hit
{
	ssize_t		wall;
	t_fixed		t;
	t_fixed		u;
}				t_hit;

# define Y_PRECISION 8

typedef struct	s_proj
{
	t_wall	wall;
	int		top;
	int		bot;
	int		is_step;
	int		step;
	int		is_ceil;
	int		ceil;
	t_mat	mat;
	t_fixed	y_iter;
	t_fixed	x_col;
	t_color	ambient;
}				t_proj;

typedef struct	s_last
{
	size_t	frame;
	int		x;
	int		start;
	int		end;
}				t_last;

void			background(t_color *buf, t_color color);
void			bresenham(t_color *buff, t_pix a, t_pix b, t_color color);
void			draw_point(t_fvec2 point, int s, t_color *buf, t_color c);

t_vec2			player_space(t_vec2 vec, t_ph physic);
void			raycast(t_game game, size_t sector_id, t_color *buf);
void			render_wall(int x, t_proj proj, t_color *buf, size_t frame);
t_color			get_wall_pixel(t_mat mat, t_proj proj, int y);

#endif
