/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_entites_update.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:46:34 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 15:57:47 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#define ID(old, start) ((size_t)old - (size_t)start) / sizeof(t_entity)

t_plist	del_update_game_events(t_game game, size_t entity, size_t e_old,
t_plist game_events)
{
	t_game_event	*curr;

	while ((curr = (t_game_event *)lpnext(&game_events)))
	{
		if ((size_t)curr->action.target > entity * sizeof(t_entity) + e_old)
			curr->action.target =
				&game.entities[ID(curr->action.target, e_old) - 1];
		else if ((size_t)curr->action.target ==
			entity * sizeof(t_entity) + e_old)
			lpremove(&game_events, (t_pelem *)curr);
		else
			curr->action.target =
			&game.entities[ID(curr->action.target, e_old)];
	}
	return (game_events);
}

t_game	del_update_entities_game_events(t_game game, size_t entity,
size_t e_old)
{
	size_t	i;
	t_plist	curr;

	i = 0;
	while (i < game.nentities)
	{
		curr = game.entities[i].self_events;
		curr = del_update_game_events(game, entity, e_old, curr);
		game.entities[i].self_events = curr;
		i++;
	}
	return (game);
}
