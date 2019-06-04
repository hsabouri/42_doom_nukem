/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:58:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 16:57:00 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

static float	check_player(t_editor_map_state editor, t_event events,
int spawn)
{
	const t_game	game = editor.env->game;

	return (circle(vec3_to_vec2((spawn) ? game.player.my_entity.spawn.pos :
				game.player.my_entity.physic.pos),
			point_from_mouse(editor, events, 0)));
}

ssize_t			select_entity(t_editor_map_state editor,
ssize_t selected_entity, t_event events, int spawn)
{
	float			min;
	ssize_t			min_id;
	size_t			i;
	float			current;
	const t_game	game = editor.env->game;

	if (events.mouse[SDL_BUTTON_LEFT] && selected_entity >= 0)
		return (selected_entity);
	i = 0;
	min = 20 / editor.zoom;
	min_id = -1;
	while (i < game.nentities)
	{
		current = circle(vec3_to_vec2((spawn) ? game.entities[i].spawn.pos :
			game.entities[i].physic.pos), point_from_mouse(editor, events, 0));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	if ((current = check_player(editor, events, spawn)) <= min)
		min_id = game.nentities;
	return (min_id);
}
