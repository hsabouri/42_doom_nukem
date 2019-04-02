/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/04/02 18:43:12 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

// TEST // SET entities to 0

t_game ft_reset_log(t_game game)
{
    t_game n_game;
    n_game = game;

    t_entity Z_E = ((t_entity){
		-2,
		(t_ph) {
			0,
			0,
			0,
            0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0,
			0,
			0,
            0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			0,
			0,
			0
		},
		0,
		0,
        0
		});

        t_trigger trig_Z = ((t_trigger){Z_E, TRIGGER_NO, Z_E});

        int i = 0;
        while(i < 3)
        {
            n_game.log[i] = trig_Z;
            i++;
        }
    return(n_game);
}

//////////


int    no_trigger(t_trigger trigger, t_trigger c_log)
{
    return 1;
}

int      see_trigger(t_trigger trigger, t_trigger c_log)
{
      if (trigger.condi == TRIGGER_SEE && trigger.condi == c_log.condi 
      && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id){
           ft_putendl("SEE !!!");
            return 1;
            }
        return 0;
}

int      touch_trigger(t_trigger trigger, t_trigger c_log)
{
      if (trigger.condi == TRIGGER_TOUCH && trigger.condi == c_log.condi && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id){
            ft_putendl("TOUCH !!!");
            return 1;
        }
        return 0;
}

int      interact_trigger(t_trigger trigger, t_trigger c_log)
{
    // Need 2nd Collision for interaction
}

int      sector_trigger(t_trigger trigger, t_trigger c_log)
{

        if (trigger.condi == TRIGGER_SECTOR && trigger.condi == c_log.condi && trigger.e_actif.physic.sector_id == c_log.e_actif.physic.sector_id){
            printf("WELCOME IN SECTOR : %d\n", c_log.e_actif.physic.sector_id);
            return 1;
        }
        return 0;
}


t_game  general_conditions(t_game game, t_trigger c_log, t_event events)
{
        t_game n_game;

        n_game = game;

        // player touch bad entities
       if(c_log.condi == TRIGGER_TOUCH && n_game.player.my_entity.id == c_log.e_actif.id && c_log.e_passif.damage == 1)
            n_game.chunks = stack_sounds(n_game.chunks, 3, 1);
    if (events.mouse_click[SDL_BUTTON_LEFT] && c_log.condi == TRIGGER_SEE && n_game.player.my_entity.id == c_log.e_actif.id && c_log.e_passif.damage == 1)
            n_game.chunks = stack_sounds(n_game.chunks, 2, 1);
        return n_game;
}

// int    (* ft_trigger[5])(t_trigger trigger, t_trigger c_log) = {no_trigger, see_trigger,touch_trigger,interact_trigger,sector_trigger};

t_env     init_conditions(t_env env)
{
    t_env n_env;

    n_env = env;

    ft_trigger *pouet = malloc(sizeof(ft_trigger) * 5);
    pouet[0] = no_trigger;
    pouet[1] = see_trigger;
    pouet[2] = touch_trigger;
    pouet[3] = interact_trigger;
    pouet[4] = sector_trigger; 

    n_env.condition = pouet;

    return n_env;

}

t_game    check_conditions(t_game game, t_event events, ft_trigger *triggers)
{
    // t_game          n_game;
    t_game_event    *current;

    // n_game = game;
    int j = 0;

    while ((current = (t_game_event *)lpnext(&game.waiting_events)) != NULL) {

        // printf("CURRENT thing check : By ENT %d to ENT %d \n", current->trigger.e_actif.id, current->trigger.e_passif.id);
            

        //  printf("Hello\n");
        while (j < game.nlog) {
        
           game = general_conditions(game, game.log[j], events);
           
            if (triggers[current->trigger.condi] (current->trigger, game.log[j]) == 1)
            {
           
                if (current->trigger.condi == TRIGGER_SECTOR)
                {
                    game.chunks = stack_sounds(game.chunks, 4, 1);
                    
                }
                lremove(&game.waiting_events, current);
                // ft_putendl("Hello my dear");
                printf("By ENT %d to ENT %d \n", current->trigger.e_actif.id, current->trigger.e_passif.id );
            }
            j++;
        }
        j = 0;

    }
    printf("List : %zu \n", game.waiting_events.len);
    return (game);
}