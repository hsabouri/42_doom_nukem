/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/04/06 17:17:29 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int    no_trigger(t_trigger trigger, t_trigger c_log)
{
    return 1;
}

int      see_trigger(t_trigger trigger, t_trigger c_log)
{
      if (trigger.condi == TRIGGER_SEE && trigger.condi == c_log.condi 
      && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id){
           ft_putstr("SEE ");
            return 1;
            }
        return 0;
}

int      touch_trigger(t_trigger trigger, t_trigger c_log)
{
      if (trigger.condi == TRIGGER_TOUCH && trigger.condi == c_log.condi && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id){
            ft_putstr("TOUCH ");
            return 1;
        }
        return 0;
}

int      interact_trigger(t_trigger trigger, t_trigger c_log)
{
       if (trigger.condi == TRIGGER_INTERACT && trigger.condi == c_log.condi && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id){
            ft_putstr("INTERACT ");
            return 1;
        }
        return 0;
}

int      sector_trigger(t_trigger trigger, t_trigger c_log)
{

        if (trigger.condi == TRIGGER_SECTOR && trigger.condi == c_log.condi && trigger.e_actif.physic.sector_id == c_log.e_actif.physic.sector_id){
            printf("WELCOME IN SECTOR : %d\n", c_log.e_actif.physic.sector_id);
            return 1;
        }
        return 0;
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


t_game  general_conditions(t_game game, t_event events)
{
        t_game n_game;
        t_trigger       *c_log;

        n_game = game;
        int j;


        j = 0;
        while ((c_log = (t_trigger *)anth(&game.log, j)) != NULL)
        {
            if(c_log->condi == TRIGGER_TOUCH && n_game.player.my_entity.id == c_log->e_actif.id && c_log->e_passif.damage == 1)
                  n_game.chunks = stack_sounds(n_game.chunks, 1, 1);
            if (events.mouse_click[SDL_BUTTON_LEFT] && c_log->condi == TRIGGER_SEE && n_game.player.my_entity.id == c_log->e_actif.id && c_log->e_passif.damage == 1)
                n_game.chunks = stack_sounds(n_game.chunks, 2, 1);
            
            j++;
        }
        return n_game;
}

t_game    check_conditions(t_game game, t_event events, ft_trigger *triggers)
{
    t_game_event    *current;
    t_trigger       *c_log;

    int j = 0;

    printf("LOG LEN %d\n", game.log.len);
    game = general_conditions(game, events);
    while ((current = (t_game_event *)lpnext(&game.waiting_events)) != NULL) {
        
        // while (j < game.nlog) {

        while ((c_log = (t_trigger *)anth(&game.log, j)) != NULL) {

            printf("DETECTED : LOG ENT %d LOG ENT %d \n", c_log->e_actif.id, c_log->e_passif.id );
            
            if (triggers[current->trigger.condi] (current->trigger, *c_log) == 1)
            {
                lremove(&game.waiting_events, current);
                printf("$$$$$$$$$$$$$$$$$ %d to $$$$$$$$$$$$$$$$$$ %d \n", current->trigger.e_actif.id, current->trigger.e_passif.id );
            }
            j++;
        }
        j = 0;

    }
    // printf("List : %zu \n", game.waiting_events.len);
    game.log.len = 0;
    return (game);
}