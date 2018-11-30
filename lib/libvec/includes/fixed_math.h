/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:36:02 by hugo              #+#    #+#             */
/*   Updated: 2018/11/28 17:42:48 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_MATH_H
# define FIXED_MATH_H
# include <sys/types.h>
# include <math.h>

# define SUB_BITS 14

typedef int32_t		t_fixed;

t_fixed		f_mul(t_fixed a, t_fixed b);
t_fixed		f_div(t_fixed a, t_fixed b);
t_fixed		f_add_int(t_fixed a, int32_t b);
t_fixed		f_sub_int(t_fixed a, int32_t b);

int32_t		f_to_int(t_fixed num);
t_fixed		f_from_int(int32_t num);
float		f_to_float(t_fixed num);
t_fixed		f_from_float(float val);

t_fixed		f_sqrt(t_fixed n);
t_fixed		f_inv_sqrt(t_fixed n);

#endif