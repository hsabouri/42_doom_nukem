/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 12:22:53 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/22 13:21:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec2	vec3_to_vec2(t_vec3 vec)
{
	return ((t_vec2){vec.x, vec.y});
}

inline t_vec3	vec2_to_vec3(t_vec2 vec)
{
	return ((t_vec3){vec.u, vec.v, 0});
}