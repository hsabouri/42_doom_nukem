/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:35:03 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/26 18:30:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>
/*

t_editor	select_multi_points(t_editor editor, t_event events, ssize_t point)
{
	ssize_t tmp;

	if (events.mouse_click[SDL_BUTTON_LEFT] && editor.sel_point >= 0)
	{
		if (editor.points_wall[0] == point)
			editor.points_wall[0] = -1;
		else if (editor.points_wall[1] == point)
			editor.points_wall[1] = -1;
		else if (editor.points_wall[0] < 0)
			editor.points_wall[0] = point;
		else
			editor.points_wall[1] = point;
		if (editor.points_wall[0] >= 0 && editor.points_wall[1] >= 0)
		{
			tmp = editor.points_wall[0];
			editor.points_wall[0] = editor.points_wall[1];
			editor.points_wall[1] = tmp;
		}
	}
	return (editor);
}

ssize_t		select_wall(t_game game, t_editor editor, t_event events)
{
	float	min;
	ssize_t	min_id;
	size_t	i;
	float	current;

	i = 0;
	min = 10 / editor.zoom;
	min_id = -1;
	while (i < game.nwalls)
	{
		current = capsule(game.points[game.walls[i].a],\
			game.points[game.walls[i].b], point_from_mouse(events, editor));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	return (min_id);
}

*/