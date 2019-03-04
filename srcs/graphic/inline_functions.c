/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/02 14:44:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

inline int		is_left(t_fvec2 a, t_fvec2 b)
{
	return (fvec2_cross(a, b).z >= 0);
}

inline t_fvec2	take_left(t_fvec2 a, t_fvec2 b)
{
	if (is_left(a, b))
		return (b);
	else
		return (a);
}

inline t_fvec2	take_right(t_fvec2 a, t_fvec2 b)
{
	if (!is_left(a, b))
		return (b);
	else
		return (a);
}
