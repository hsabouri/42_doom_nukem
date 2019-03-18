/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/16 19:02:58 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

inline int		is_left(const t_fvec2 a, const t_fvec2 b)
{
	return (fvec2_cross(a, b).z >= 0);
}

inline t_fvec2	take_left(const t_fvec2 a, const t_fvec2 b)
{
	if (is_left(a, b))
		return (b);
	else
		return (a);
}

inline t_fvec2	take_right(const t_fvec2 a, const t_fvec2 b)
{
	if (!is_left(a, b))
		return (b);
	else
		return (a);
}
