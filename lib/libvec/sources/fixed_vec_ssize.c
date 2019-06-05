/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_ssize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:37 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/07 13:48:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_fixed	fvec3_ssize(t_fvec3 a)
{
	return (f_mul(a.x, a.x) + f_mul(a.y, a.y) + f_mul(a.z, a.z));
}

inline t_fixed	fvec2_ssize(t_fvec2 a)
{
	return (f_mul(a.u, a.u) + f_mul(a.v, a.v));
}
