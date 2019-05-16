/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:00:23 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/15 17:32:50 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	add_events(t_game *game, t_entity e_actif, t_condition condi,
t_entity e_passif)
{
	t_game_event *elem;
	
	elem = (t_game_event *)malloc(sizeof(t_game_event));
	*elem = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger) {
			e_actif, condi, e_passif
		}
	};
	lppush(&game->waiting_events, (t_pelem *)elem);
}
