/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:38:21 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/24 14:40:29 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_VEC_H
# define FIXED_VEC_H

# include <fixed_math.h>

typedef struct	s_fvec3
{
	t_fixed		x;
	t_fixed		y;
	t_fixed		z;
}				t_fvec3;

typedef struct	s_fvec2
{
	t_fixed		u;
	t_fixed		v;
}				t_fvec2;

t_fvec3			fvec3_new(t_fixed x, t_fixed y, t_fixed z);
t_fvec3			fvec3_scale(t_fvec3 a, t_fixed s);
t_fvec3			fvec3_add(t_fvec3 a, t_fvec3 b);
t_fvec3			fvec3_sub(t_fvec3 a, t_fvec3 b);
t_fixed			fvec3_ssize(t_fvec3 a);
t_fixed			fvec3_dot(t_fvec3 a, t_fvec3 b);
t_fvec3			fvec3_cross(t_fvec3 a, t_fvec3 b);
t_fvec3			fvec3_mult(t_fvec3 a, t_fvec3 b);
t_fvec3			fvec3_rot(t_fvec3 a, t_fvec3 b);
t_fixed			fvec3_ssize(t_fvec3 a);
t_fvec3			fvec2_to_fvec3(t_fvec2 a);
t_fvec2			fvec3_to_fvec2(t_fvec3 a);
t_fvec2			fvec2_new(t_fixed u, t_fixed v);
t_fvec2			fvec2_scale(t_fvec2 a, t_fixed s);
t_fvec2			fvec2_add(t_fvec2 a, t_fvec2 b);
t_fvec2			fvec2_sub(t_fvec2 a, t_fvec2 b);
t_fixed			fvec2_dot(t_fvec2 a, t_fvec2 b);
t_fvec3			fvec2_cross(t_fvec2 a, t_fvec2 b);
t_fvec2			fvec2_mult(t_fvec2 a, t_fvec2 b);
t_fvec2			fvec2_rot(t_fvec2 a, t_fvec2 b);
t_fixed			fvec2_ssize(t_fvec2 a);

#endif
