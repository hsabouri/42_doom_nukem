/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:07:20 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/12 10:52:42 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSIC_H
# define PHYSIC_H

/*
** This header contains all the structures used to calculate the physic in a
** highly optimized manner.
*/

# include <structure.h>

# define MAX_JUMP 2
# define MAX_FALL -0.3
# define EPSILON 0.5

# define SPEED_MULTIPLY 2
# define FALL_MULTIPLY 4

typedef struct	s_tp
{
	t_portal	portal;
	t_wall		from_wall;
	t_wall		to_wall;
	int			portal_in;
	int			portal_out;
}				t_tp;

typedef struct	s_touch
{
	int			wall;
	float		dist;
	t_vec3		pos;
}				t_touch;

typedef struct	s_last_pos
{
	u_int32_t	sector_id;
	t_vec3		pos;
}				t_last_pos;

typedef struct	s_ph_info
{
	t_game	*game;
	float	old_timer;
	int		wall;
	t_ph	*physic;
}				t_ph_info;

int				seg_seg(t_vec3 next_pos, t_ph physic, t_touch *touch,
	t_game game);
float			z_inter(t_sector sector, t_vec3 pos, int mode);
t_touch			collision(t_vec3 next_pos, t_ph physic, t_game game, int wall);
t_vec3			col_entities(t_ph n_physic, t_ph physic, t_game *game,
	size_t id);
void			col_interact(t_ph n_physic, t_game *game, size_t id);
t_vec3			floor_col(float pos_z, t_sector sector, t_vec3 speed,
	u_int32_t *jump);
t_vec3			ceil_col(t_vec3 pos, t_sector sector, t_vec3 speed);
t_vec3			slide_wall(t_vec3 next_pos, t_game game, t_wall wall);
u_int32_t		is_in_sector(t_ph physic, t_game game, u_int32_t sector_id);
t_ph			entities_physic(t_ph physic, t_game *game, ssize_t id,
	float old_timer);
t_ph			entities_track(t_ph physic, t_game game, t_last_pos last_pos);
void			set_tp(t_tp *teleport, t_touch touch, t_game game);
t_vec3			teleportation(t_vec3 pos, t_game *game, t_tp teleport,
	t_ph *physic);
u_int32_t		point_in_circle(t_ph entity_1, t_ph entity_2);
float			circle_circle(t_ph entity_1, t_ph entity_2, t_col_mode col);
int				interact(t_ph entity_1, t_ph entity_2);
t_vec3			move_entities(t_ph *physic, t_game *game, int wall,
				float old_timer);

#endif
