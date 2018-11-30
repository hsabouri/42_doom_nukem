/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:22:02 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 13:42:10 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_MATH_H
# define FLOAT_MATH_H

# include <sys/types.h>
# include <float.h>

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

float	fast_inv_sqrt(float x);
float	fast_sqrt(float x);

#endif
