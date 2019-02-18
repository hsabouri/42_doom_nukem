/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:27:41 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/18 15:56:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include <graphic_singletons.h>
# include <structure.h>

# define WIDTH 720
# define HEIGHT 480
# define PWIDTH	2.5
# define RATIO WIDTH / PWIDTH
# define PDIS 0.8

# define WHITE		(t_color){255,255,255,255}
# define GREY		(t_color){128,128,128,255}
# define RED		(t_color){255,0,0,255}
# define GREEN		(t_color){0,255,0,255}
# define BLUE		(t_color){0,0,255,255}
# define BLACK		(t_color){0,0,0,255}
# define NO_COLOR	(t_color){0,0,0,0}

# define UBE		(t_color){125,122,188,255}
# define LIBERTY	(t_color){100,87,166,255}
# define TRACTOR_R	(t_color){239,20,54,255}
# define LOW_R		(t_color){139,10,24,255}
# define RICH_BLACK	(t_color){0,20,33,255}
# define MOONSTONE	(t_color){98,190,193,255}
# define MUSTARD	(t_color){255,224,102,255}

# define TEXT_MAX	256

typedef struct	s_pix
{
	int32_t	x;
	int32_t	y;
}				t_pix;

typedef struct	s_ray
{
	t_fvec2		dir;
	int			id;
	ssize_t		mask_wall;
}				t_ray;

# define Y_PRECISION 8

typedef struct	s_wall_proj
{
	t_fixed		tex_x;
	t_fixed		tex_y_iter;
	t_mat		wall;
	u_int32_t	id;
}				t_wall_proj;

typedef struct	s_h_proj
{
	t_fvec2		ray;
	t_fixed		z_axis;
	t_fvec2		pos;
	t_fvec2		h;
	t_mat		floor;
	u_int32_t	fl_id;
	t_mat		ceiling;
	u_int32_t	cl_id;
}				t_h_proj;

typedef struct	s_tex_proj
{
	t_sector	sector;
	t_wall		wall;
}				t_tex_proj;

typedef struct	s_proj
{
	int			not_found;
	int			top;
	int			bot;
	int			is_step;
	int			step;
	int			is_ceil;
	int			ceil;
	u_int32_t	st_id;
	u_int32_t	tp_id;
	t_wall_proj	w_proj;
	t_h_proj	h_proj;
	t_tex_proj	tex_proj;
	u_int32_t	*id_buf;
}				t_proj;


# include "srcs/graphic/bresenham.h"

void			background(t_color *buf, t_color color);
void			draw_point(t_fvec2 point, int s, t_color *buf, t_color c);

t_vec2			player_space(t_vec2 vec, t_ph physic);
void			raycast(t_game game, size_t sector_id, t_color *buf);
void			render_wall(int x, t_proj proj, t_color *buf, size_t frame);

t_color			get_floor_pixel(t_h_proj w_proj, t_tex_proj tex_proj, int y);
t_color			get_roof_pixel(t_h_proj w_proj, t_tex_proj tex_proj, int y);
t_color			get_wall_pixel(t_wall_proj w_proj, t_tex_proj tex_proj, int y);

#endif
