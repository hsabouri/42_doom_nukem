/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:37:55 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/21 17:52:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_fvec3		fvec3_new(t_fixed x, t_fixed y, t_fixed z)
{
	return ((t_fvec3) {x, y, z});
}

inline t_fvec2		fvec2_new(t_fixed u, t_fixed v)
{
	return ((t_fvec2) {u, v});
}
