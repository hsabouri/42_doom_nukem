/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:07:30 by hugo              #+#    #+#             */
/*   Updated: 2019/05/30 17:12:34 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./color.h"

inline t_color	color_filter(t_color a, t_color filter)
{
	return ((t_color) {
		.a = (a.a * filter.a) >> 8,
		.b = (a.b * filter.b) >> 8,
		.g = (a.g * filter.g) >> 8,
		.r = (a.r * filter.r) >> 8,
	});
}

inline t_color	color_superpose(t_color a, t_color b)
{
	if (b.a > 0)
		return (b);
	else
		return (a);
}
