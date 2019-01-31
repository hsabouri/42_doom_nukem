/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:22:02 by hugo              #+#    #+#             */
/*   Updated: 2019/01/30 16:04:18 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_MATH_H
# define FLOAT_MATH_H

# include <sys/types.h>
# include <float.h>

# ifndef M_PI
#  define M_PI 3.141592653
# endif

typedef union	u_sqrt
{
	int32_t	i;
	float	x;
}				t_sqrt;

typedef union	u_inv_sqrt
{
	float	x;
	int32_t	i;
}				t_inv_sqrt;

float			fast_inv_sqrt(float x);
float			fast_sqrt(float x);
float			clamp(float x, float min, float max);

#endif
