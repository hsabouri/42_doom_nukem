/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:16:54 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 20:13:23 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_VEC_H
# define FLOAT_VEC_H

# include <math.h>

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	s;
	float	z;
}				t_vec3;

typedef struct	s_vec2
{
	float	u;
	float	v;
	float	s;
}				t_vec2;

t_vec3	vec3_new(float x, float y, float z);
t_vec3	vec3_scale(t_vec3 a, float s);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
float	vec3_size(t_vec3 a);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_rot(t_vec3 a, t_vec3 r);
t_vec3	vec3_rot_x(t_vec3 a, float t);
t_vec3	vec3_rot_y(t_vec3 a, float t);
t_vec3	vec3_rot_z(t_vec3 a, float t);

t_vec2	vec2_new(float u, float v);
t_vec2	vec2_scale(t_vec2 a, float s);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_sub(t_vec2 a, t_vec2 b);
float	vec2_size(t_vec2 a);
float	vec2_dot(t_vec2 a, t_vec2 b);
t_vec3	vec2_cross(t_vec2 a, t_vec2 b);
t_vec2	vec2_mult(t_vec2 a, t_vec2 b);
t_vec2	vec2_rot(t_vec2 a, float t);

#endif