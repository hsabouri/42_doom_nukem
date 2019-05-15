/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_events_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:22:28 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/15 11:59:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_plist		parse_events(void *buf, t_save save, size_t n_events,\
t_game game, t_player player)
{
	t_c_game_event	struc_e;
	t_plist			event;
	t_game_event	*current;
	size_t			i;
	size_t			j;

	event = lpnew(NULL);
	i = 0;
	while (i < n_events)
	{
		struc_e = *(t_c_game_event *)dump_struct(buf, save.index
			+ sizeof(t_c_game_event) * i, sizeof(t_c_game_event), save.max);
		verify_magic(&struc_e, EVENT_MAGIC, i);
		current = (t_game_event *)safe_malloc(sizeof(t_game_event), "loader");
		current->elem = (t_pelem){NULL, NULL};
		if (struc_e.trigger.e_actif == -1)
			current->trigger.e_actif = player.my_entity;
		else
		{
			j = 0;
			while (j < game.nentities)
			{
				if (struc_e.trigger.e_actif == game.entities[j].id)
				{
					current->trigger.e_actif = game.entities[j];
					break;
				}
				j++;
			}
		}
		current->trigger.condi = struc_e.trigger.condi;
		if (struc_e.trigger.e_passif == -1)
			current->trigger.e_passif = player.my_entity;
		else
		{
			j = 0;
			while (j < game.nentities)
			{
				if (struc_e.trigger.e_passif == game.entities[j].id)
				{
					current->trigger.e_passif = game.entities[j];
					break;
				}
				j++;
			}
		}
		lppush(&event, (t_pelem *)current);
		i++;
	}
	return (event);
}
