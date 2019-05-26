/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:16:10 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:40:42 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <fixed_math.h>
# include <fixed_vec.h>
# include <float_math.h>
# include <float_vec.h>

t_vec3			fvec3_to_vec3(t_fvec3 fvec);
t_vec2			fvec2_to_vec2(t_fvec2 fvec);

t_fvec3			vec3_to_fvec3(t_vec3 vec);
t_fvec2			vec2_to_fvec2(t_vec2 vec);

#endif
