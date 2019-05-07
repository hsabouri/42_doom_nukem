/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:27:41 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/07 13:04:02 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include <graphic_singletons.h>
# include <structure.h>

# define WIDTH 1280
# define HEIGHT 720
# define PWIDTH	2.5
# define RATIO (WIDTH / PWIDTH)
# define PDIS 0.8
# define N_THREADS 8

# define WHITE		(t_color){255,255,255,255}
# define GREY		(t_color){128,128,128,255}
# define RED		(t_color){255,0,0,255}
# define GREEN		(t_color){0,255,0,255}
# define BLUE		(t_color){0,0,255,255}
# define ORANGE		(t_color){251,126,20,255}
# define BLACK		(t_color){0,0,0,255}
# define NO_COLOR	(t_color){0,0,0,0}

# define UBE		(t_color){125,122,188,255}
# define LIBERTY	(t_color){100,87,166,255}
# define TRACTOR_R	(t_color){239,20,54,255}
# define LOW_R		(t_color){139,10,24,255}
# define RICH_BLACK	(t_color){0,20,33,255}
# define MOONSTONE	(t_color){98,190,193,255}
# define MUSTARD	(t_color){255,224,102,255}
# define PORTAL_B	(t_color){62,189,236,255}
# define PORTAL_O	(t_color){233,131,31,255}
# define E_DAMAGE	(t_color){222,62,65,255}
# define E_PEACEFUL	(t_color){100,100,100,255}
# define E_PLAYER	(t_color){128,232,88,255}

# define TEXT_MAX	256

typedef struct	s_pix
{
	int32_t	x;
	int32_t	y;
}				t_pix;

# define NCACHEWALL 20

typedef struct	s_hit
{
	int		hit;
	t_fvec2	ray;
	t_fvec2	ratios;
}				t_hit;

typedef struct	s_context
{
	int			left;
	int			right;
	t_ph		physic;
	ssize_t		mask;
	t_sector	sector;
}				t_context;

typedef struct	s_cache_wall
{
	int32_t	portal;
	size_t	id;
	t_fixed	size;
	t_fvec2	tex_pos;
	t_fvec2	a;
	t_fvec2	b;
	t_mat	mat;
	t_mat	*open;
	t_vec2	left_z;
	t_vec2	right_z;
}				t_cache_wall;

typedef struct	s_cache_entity
{
	size_t			id;
	t_fvec2			a;
	t_fvec2			b;
	t_fixed			h;
	t_fixed			dis;
	t_ph			physic;
	t_mat			*mat;
}				t_cache_entity;

typedef struct	s_bunch
{
	int				nwalls;
	int				nentities;
	t_cache_wall	walls[NCACHEWALL];
	t_cache_entity	entities[NCACHEWALL];
}				t_bunch;

typedef struct	s_section
{
	t_cache_wall	wall;
	t_sector		next;
	int				start;
	int				end;
	t_fvec2			a;
	t_fvec2			b;
}				t_section;

typedef struct	s_section_entity
{
	t_cache_entity	entity;
	int				start;
	int				end;
	t_fvec2			a;
	t_fvec2			b;
}				t_section_entity;

typedef struct	s_tex_proj
{
	t_color		ambient;
	t_mat		mat;
	int			x;
	int			angle;
}				t_tex_proj;

typedef struct	s_pl_proj
{
	u_int32_t	uid_roof;
	u_int32_t	uid_floor;
	int			look_v;
	int			is_skybox;
	t_fvec2		wr;
	t_fvec2		ray;
	t_fvec2		h;
	t_fvec2		pos;
	t_tex_proj	tex_floor;
	t_tex_proj	tex_roof;
}				t_pl_proj;

typedef struct	s_proj
{
	u_int32_t	uid;
	u_int32_t	uid_step;
	u_int32_t	uid_ceil;
	t_tex_proj	tex_wall;
	int			is_portal_tex;
	t_tex_proj	tex_open;
	t_pl_proj	plane;
	int			top;
	int			ceil;
	int			step;
	int			bot;
	t_fixed		u;
	t_fixed		x;
	t_fixed		y_iter;
	t_fixed		y_start;
}				t_proj;

typedef struct	s_e_proj
{
	u_int32_t	uid;
	t_mat		mat;
	t_tex_proj	tex;
	int			top;
	int			bot;
	t_fixed		y_start;
	t_fixed		u;
	t_fixed		x;
	t_fixed		y_iter;
}				t_e_proj;

typedef struct	s_render
{
	int			nentities;
	int			nsections;
	int			nportals;
	t_section	sections[NCACHEWALL];
	t_section_entity	entities[NCACHEWALL];
	t_section	portals[NCACHEWALL]; //probably need to change type
}				t_render;

void			render(const t_game game, const t_context context, t_color *buf, u_int32_t *id_buf);

# include "srcs/graphic/bresenham.h"

int				is_left(t_fvec2 a, t_fvec2 b);
t_fvec2			take_left(t_fvec2 a, t_fvec2 b);
t_fvec2			take_right(t_fvec2 a, t_fvec2 b);

void			background(t_color *buf, t_color color, t_pix size);
void			draw_point(t_fvec2 point, int s, t_color *buf, t_color c);

t_vec2			player_space(t_vec2 vec, t_ph physic);

void			draw_wall(int id, t_proj proj, t_color *buf,
				u_int32_t *ids);
void			draw_portal(int id, t_proj proj, t_color *buf,
				u_int32_t *ids);
void			draw_entity(int id, t_e_proj proj, t_color *buf,
				u_int32_t *ids);

t_proj			wall_projection(int id, t_hit hit, t_context context,
				t_section section);
t_proj			portal_projection(int id, t_hit hit, t_context context,
				t_section section);
t_e_proj		entity_projection(t_hit hit, t_context context,
				t_section_entity section);

t_bunch			build_bunch(t_game game, t_context context, t_limit limit);
t_render		build_sections(t_context context, t_bunch bunch,
				t_limit limits);
t_render		build_sections_portals(t_render render);

t_color			get_floor_pixel(t_pl_proj proj, t_tex_proj tex, int y);
t_color			get_roof_pixel(t_pl_proj proj, t_tex_proj tex, int y);
t_color			get_wall_pixel(t_proj proj, int y);
t_color			get_portal_pixel(t_proj proj, int y);
t_color			get_entity_pixel(t_e_proj proj, int y);
t_color			get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix, char p, int y_s);

t_fvec2			get_ray_dir(t_ph physic, int id);
int				get_ray_id(t_fvec2 point, t_limit limit,
				t_context context, int max);
t_limit			build_limits(t_context context);
int				is_in_limit(t_limit limit, t_fvec2 a, t_fvec2 b);

t_hit			ray_seg(t_fvec2 a, t_fvec2 b, t_fvec2 c, t_fvec2 d);

void			render_wall(t_context context, t_section section,
				t_color *buf, u_int32_t *ids);

void			render_portal(t_context context, t_section section,
				t_color *buf, u_int32_t *ids);
void			render(t_game game, t_context context,
				t_color *buf, u_int32_t *id_buf);

t_sector		teleport_sector(t_game game, t_context context, t_section section);
t_context		teleport(t_game game, t_context context, t_section section);
void			find_center_sectors(t_game game);
void			find_center(t_game game, size_t i);
void			sort_tab_z(size_t n, unsigned int i, t_game game);
void			rotate_y(size_t n, int mode, t_game game);
int				wall_from_point(size_t n, int point, t_game game, int i);
unsigned int	find_right(t_game game, int* tab, size_t n, int i);
unsigned int	find_left(t_game game, int* tab, size_t n, int i);
void			rotate_floor(size_t n, int mode, t_game game);
void			rotate_ceiling(size_t n, int mode, t_game game);
void			reverse_walls(t_game game, size_t n);
#endif
