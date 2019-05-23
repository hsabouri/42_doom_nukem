/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/06/08 16:05:43 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include "./triggers.h"

t_env	init_conditions(void)
{
	t_env		env;
	ft_trigger	*condi;

	condi = malloc(sizeof(ft_trigger) * 5);
	condi[0] = no_trigger;
	condi[1] = see_trigger;
	condi[2] = touch_trigger;
	condi[3] = interact_trigger;
	condi[4] = sector_trigger;
	env.condition = condi;
	return (env);
}

t_game	general_conditions(t_game game, t_event events)
{
	t_trigger	*c_log;
	int			j;

	j = 0;
	if (events.keys[SDL_SCANCODE_L])
		add_events(&game, game.player.my_entity, TRIGGER_SEE, game.entities[1]);
	while ((c_log = (t_trigger *)anth(&game.log, j)) != NULL)
	{
		if (c_log->condi == TRIGGER_TOUCH && game.player.my_entity.id
			== c_log->e_actif.id && c_log->e_passif.damage == 1)
			game.chunks = stack_sounds(game.chunks, 1, 1);
		if (events.mouse_click[SDL_BUTTON_LEFT] && c_log->condi
			== TRIGGER_SEE && game.player.my_entity.id == c_log->e_actif.id
			&& c_log->e_passif.damage == 1)
			game.chunks = stack_sounds(game.chunks, 2, 1);
		j++;
	}
	return (game);
}

t_game	check_conditions(t_game game, t_event events, ft_trigger *triggers)
{
	t_game_event	*current;
	t_trigger		*c_log;
	int				j;

	j = 0;
	game = general_conditions(game, events);
	while ((current = (t_game_event *)lpnext(&game.waiting_events)) != NULL)
	{
		while ((c_log = (t_trigger *)anth(&game.log, j)) != NULL)
		{
			if (triggers[current->trigger.condi](current->trigger, *c_log) == 1)
			{
				lpremove(&game.waiting_events, (t_pelem *)current);
			}
			j++;
		}
		j = 0;
	}
	game.log.len = 0;
	return (game);
}
