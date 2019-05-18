/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:47:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/18 18:53:29 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

void        spawn_entity(t_vec2 pos, size_t class_type, t_game game)
{
    create_entity(pos, 0, game);
    // assign_entity(t_assign_entity *state, t_game game)

    
}

void        kill_entity(t_entity, t_game game)
{
    /*
    int i;

    entity->life = 0;
    i = 0; 
    while(game.entity[i] != entity_id)
    {
        i++;
    }
    delete_entity(i, game)

    */
}

void        animate_sector(t_sector * move_sector)
{
    /*
        if (is_animate == false)
            if(M_S.F == A)
                animate(&move_sector.floor, move_sector.B_pos_floor)
            if(M_S.C == A)
                animate(&move_sector.ceiling, move_sector.B_pos_ceiling)
            if(M_S.F == B)
                animate(&move_sector.floor, move_sector.A_pos_floor)
            if(M_S.C == B)
                animate(&move_sector.ceiling, move_sector.A_pos_ceiling)
        }
    */
}

void        health_down(int entity_id)
{

}

void        health_up()
{
    
}


