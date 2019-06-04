/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:08:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 16:58:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

void		select_multi(ssize_t curr, ssize_t *dual, t_event events)
{
	if (events.mouse_click[SDL_BUTTON_LEFT] && curr >= 0)
	{
		if (dual[0] == curr)
			dual[0] = -1;
		else if (dual[0] == -1)
			dual[0] = curr;
		else if (dual[1] == -1)
			dual[1] = curr;
	}
	else if (events.mouse_click[SDL_BUTTON_LEFT])
		dual[0] = -1;
}

ssize_t		select_point(t_editor_map_state editor, ssize_t selected_point,
t_event events)
{
	float			min;
	ssize_t			min_id;
	size_t			i;
	float			current;
	const t_game	game = editor.env->game;

	if (events.mouse[SDL_BUTTON_LEFT] && selected_point >= 0)
		return (selected_point);
	i = 0;
	min = 20 / editor.zoom;
	min_id = -1;
	while (i < game.npoints)
	{
		current = circle(game.points[i], point_from_mouse(editor, events, 0));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	return (min_id);
}

ssize_t		select_wall(t_editor_map_state editor, ssize_t selected_wall,
t_event events)
{
	float			min;
	ssize_t			min_id;
	size_t			i;
	float			current;
	const t_game	game = editor.env->game;

	if (events.mouse[SDL_BUTTON_LEFT] && selected_wall >= 0)
		return (selected_wall);
	i = 0;
	min = 10 / editor.zoom;
	min_id = -1;
	while (i < game.nwalls)
	{
		current = capsule(game.points[game.walls[i].a],\
			game.points[game.walls[i].b], point_from_mouse(editor, events, 0));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	return (min_id);
}

ssize_t		select_unassigned_wall(t_editor_map_state editor,
ssize_t selected_wall, t_event events)
{
	float			min;
	ssize_t			min_id;
	size_t			i;
	float			current;
	const t_game	game = editor.env->game;

	if (events.mouse[SDL_BUTTON_LEFT] && selected_wall >= 0)
		return (selected_wall);
	i = game.nwalls;
	min = 10 / editor.zoom;
	min_id = -1;
	while (i < game.nwalls + game.nuwalls)
	{
		current = capsule(game.points[game.walls[i].a],\
			game.points[game.walls[i].b], point_from_mouse(editor, events, 0));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i - game.nwalls;
		}
		i++;
	}
	return (min_id);
}
