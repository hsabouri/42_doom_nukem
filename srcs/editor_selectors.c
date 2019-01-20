/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:35:03 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/06 17:36:41 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

long	select_point(t_game game, t_editor editor, t_event events)
{
	size_t	i;
	t_vec2	point;

	i = 0;
	if (events.mouse[SDL_BUTTON_LEFT] && editor.sel_point >= 0)
		return (editor.sel_point);
	if (editor.selecting == 1)
		return (-1);
	while (i < game.npoints)
	{
		point = vec2_scale(game.points[i], editor.zoom);
		point = vec2_add(point, editor.offset);
		if (events.x > point.u - POINT_SIZE &&\
		events.x <= point.u + POINT_SIZE && events.y > point.v - POINT_SIZE &&\
		events.y <= point.v + POINT_SIZE)
			return (i);
		i++;
	}
	return (-1);
}
