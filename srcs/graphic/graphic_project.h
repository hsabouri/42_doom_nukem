/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_project.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 07:10:48 by hugo              #+#    #+#             */
/*   Updated: 2019/02/19 19:07:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_PROJECT_H
# define GRAPHIC_PROJECT_H

# include <vec.h>

typedef struct	s_hit
{
	ssize_t		wall;
	t_fvec2		ray;
	t_fixed		t;
	t_fixed		u;
}				t_hit;

typedef struct	s_bunch
{
	t_sector	sector;
	u_int32_t	nwalls;
	t_i_wall	walls[100];
}				t_bunch;

t_proj			projection(t_ph physic, t_hit hit, t_sector sector[2],
				t_game game);
t_proj			ray_sector(t_ray ray, t_bunch bunch, t_game game,
				t_color *buf);
t_bunch			filter(t_game game, t_sector sector, t_vec2 r[2], t_vec2 pos, ssize_t mas);
void			build_rays(t_vec2 rays[2], t_ph physic, t_vec2 a, t_vec2 b);

#endif
