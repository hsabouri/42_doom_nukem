/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:07:20 by iporsenn          #+#    #+#             */
/*   Updated: 2019/01/04 17:07:22 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSIC_H
# define PHYSIC_H

/*
** This header contains all the structures used to calculate the physic in a
** highly optimized manner.
*/

# include <structure.h>

# define SPEED_REDUCE 7
# define MAX_JUMP 2
# define MAX_FALL -1
# define EPSILON 0.5

typedef struct      s_tp
{
    t_portal    portal;
    t_wall      from_wall;
    t_wall      to_wall;
    int         portal_in;
    int         portal_out;
}                   t_tp;

typedef struct      s_touch
{
    int     wall;
    float   dist;
}                   t_touch;

typedef struct      s_last_pos
{
    u_int32_t   sector_id;
    t_vec3      pos;
}                   t_last_pos;

int	        	seg_seg(t_vec3  next_pos, t_player player, t_touch *touch, \
                t_game game);
t_touch			collision(t_vec3 next_pos, t_game game, u_int32_t *sector_id, \
                int wall);
t_vec3	    	floor_col(float pos_z, t_sector sector, t_vec3 speed);
t_vec3	    	ceil_col(float pos_z, t_sector sector, t_vec3 speed);
t_vec3	    	slide_wall(t_vec3 next_pos, t_game game, t_wall wall);

t_player	    player_track(t_player player, t_game game, t_last_pos last_pos);

#endif
