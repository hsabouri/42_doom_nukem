/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:35:03 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/31 11:57:37 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

float		capsule(t_vec2 a, t_vec2 b, t_vec2 p)
{
	const t_vec2	pa = vec2_sub(p, a);
	const t_vec2	ba = vec2_sub(b, a);
	const float		h = clamp(vec2_dot(pa, ba) / vec2_dot(ba, ba), 0.0, 1.0);

	return (1.0 / vec2_inv_size(vec2_sub(pa, vec2_scale(ba, h))));
}

float		circle(t_vec2 a, t_vec2 p)
{
	return (1 / vec2_inv_size(vec2_sub(a, p)));
}

t_vec2		point_from_mouse(t_event events, t_editor editor)
{
	t_vec2	new_point;

	new_point = (t_vec2) {events.x, events.y};
	new_point = vec2_sub(new_point, editor.offset);
	new_point = vec2_scale(new_point, 1 / editor.zoom);
	return (new_point);
}

ssize_t		select_point(t_game game, t_editor editor, t_event events)
{
	float	min;
	ssize_t	min_id;
	size_t	i;
	float	current;

	if (events.mouse[SDL_BUTTON_LEFT] && editor.sel_point >= 0)
		return (editor.sel_point);
	if (editor.selecting == 1)
		return (-1);
	i = 0;
	min = 20 / editor.zoom;
	min_id = -1;
	while (i < game.npoints)
	{
		current = circle(game.points[i], point_from_mouse(events, editor));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	return (min_id);
}

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
