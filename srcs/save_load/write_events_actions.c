/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_events_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:00:11 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/27 15:00:13 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		write_events(int fd, t_plist event)
{
	t_c_game_event	res;
	t_game_event	*current;
	size_t			i;

	i = 0;
	while ((current = (t_game_event *)lpnext(&event)) != NULL)
	{
		res.magic = EVENT_MAGIC + i;
		if (current->trigger.e_actif.id == -1)
			res.trigger.e_actif = -1;
		else
			res.trigger.e_actif = current->trigger.e_actif.id;
		res.trigger.condi = current->trigger.condi;
		if (current->trigger.e_passif.id == -1)
			res.trigger.e_passif = -1;
		else
			res.trigger.e_passif = current->trigger.e_passif.id;
		write_struct(&res, fd, sizeof(t_c_game_event));
		i++;
	}
}
