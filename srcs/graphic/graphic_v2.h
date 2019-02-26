/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_v2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:46:10 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/26 13:45:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_V2_H
# define GRAPHIC_V2_H

# include <graphic.h>

# define NCACHEWALL 50

typedef struct	s_hit
{
	int		hit;
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

typedef struct	s_limit
{
	t_ray	left;
	t_ray	right;
}				t_limit;

typedef struct	s_cache_wall
{
	int32_t	portal;
	size_t	id;
	t_fvec2	a;
	t_fvec2	b;
	t_mat	mat;
}				t_cache_wall;

typedef struct	s_section
{
	t_cache_wall	wall;
	int				start;
	int				end;
	t_fvec2			a;
	t_fvec2			b;
}				t_section;

typedef struct	s_render
{
	int			nsections;
	int			nportals;
	t_section	sections[NCACHEWALL];
	t_section	portals[NCACHEWALL]; //probably need to change type
}				t_render;

typedef struct	s_wall_proj_tmp
{
	t_mat		mat_ceiling;
	t_mat		mat_wall;
	t_mat		mat_floor;
	int			top;
	int			bot;
	int			id;
	t_fixed		u;
	t_sector	sector;
}				t_wall_proj_tmp;

void	render(t_game game, t_context context, t_color *buf, u_int32_t *id_buf);

#endif
