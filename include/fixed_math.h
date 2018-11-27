/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:36:02 by hugo              #+#    #+#             */
/*   Updated: 2018/11/27 11:14:17 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_MATH_H
# define FIXED_MATH_H
# include <sys/types.h>

typedef struct			s_fixed
{
	int32_t		integer;
	int32_t		decimal;
}						t_fixed;

typedef struct			s_vec4
{
	t_fixed	x;
	t_fixed	y;
	t_fixed	z;
	t_fixed	s;
}						t_vec4;

typedef struct			s_vec2
{
	t_fixed	u;
	t_fixed	v;
}						t_vec2;

#endif