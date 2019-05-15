/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_ac.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/14 15:25:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EV_AC_H
# define EV_AC_H

# include "../editor_comp.h"

typedef struct	s_editor_ev_ac_state 
{
	ssize_t	selected;
	ssize_t	selected_entity;
	ssize_t selected_trigger;
	ssize_t selected_entity_2;
	int		refresh_second_entity;
	t_env	*env;
}				t_editor_ev_ac_state;

t_component		init_editor_ev_ac(t_env *env, t_sdl *sdl);
t_component		create_list_events(t_env *env, t_sdl *sdl);
t_component		create_list_entity(t_env *env, t_sdl *sdl);
t_component		create_list_trigger(t_env *env, t_sdl *sdl);
t_component		create_list_seconds_entity(t_env *env, int *external,
				t_sdl *sdl);

#endif
