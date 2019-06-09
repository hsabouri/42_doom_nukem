/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/06/09 17:44:24 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include "./triggers.h"

t_env	init_conditions(void)
{
	t_env env;
	
	ft_trigger *condi = malloc(sizeof(ft_trigger) * 5);
	condi[0] = shot_trigger;
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

void	entities_conditions(t_game *game, ft_trigger *triggers, ft_actions *actions)
{
	t_game_event    *current;
	t_entity		*check_entities;
	t_trigger       *c_log;
	int 		i;
	int			j;

	i = 0;
	j = 0;
	check_entities = game->entities;

	i = 0;
	
	// printf("Debut\n");
	while (i < game->nentities)
	{
		// printf("+ 1\n", i);
		while ((current = (t_game_event *)lpnext(&check_entities[0].self_events)) != NULL)
		{
			// printf("NEW ENTITY\n");
			while ((c_log = (t_trigger *)anth(&game->log, j)) != NULL)
			{
				// printf("LOG %d\n", j);
				if (triggers[current->trigger.condi](current->trigger, *c_log) == 1)
				{
					printf("PRE OUF %d\n", current->trigger.e_passif.id);
					printf("TARGET ENTITY %d\n",current->action.target->id);
					actions[current->action.action_type]((t_vec2){0,0},current->action.target,game,current->action.num);
					// printf("OOF %d\n", current->trigger.e_passif.id);
					if (current->trigger.condi == TRIGGER_SEE)
					{
						// printf(" -> SEE -> ");
					} 
					else if (current->trigger.condi == TRIGGER_TOUCH)
					{
						// printf(" -> TOUCH -> ");
					}
					else if (current->trigger.condi == TRIGGER_INTERACT)
					{
						// printf(" -> INTERACT -> ");
					}
					else if (current->trigger.condi == TRIGGER_SECTOR)
					{
						// printf(" -> SECTOR -> ");
					}
					else if (current->trigger.condi == TRIGGER_SHOT)
					{
						// printf(" -> SHOT -> ");
					}
					
					// printf("");
					
					
					// break;
					// printf("%d\n", current->trigger.e_passif.id);	
					// printf("PAN PAN PAN");
					game->chunks = stack_sounds(game->chunks, 5, 2);
					
					//DO ACTION ENTITY
				}
				j++;
			}
			
			j = 0;
		}
		i++;
	}
}

t_game    check_conditions(t_game game, t_event events, ft_trigger *triggers, ft_actions *actions)
{
	t_game_event	*current;
	t_trigger		*c_log;
	int				j;

	j = 0;
	game = general_conditions(game, events);
	entities_conditions(&game, triggers, actions);
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
