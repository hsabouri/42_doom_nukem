/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:52:52 by iporsenn          #+#    #+#             */
/*   Updated: 2019/01/30 16:52:55 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	player_properties(t_game game, t_event events)
{
	t_game	n_game;

	n_game = game;
	n_game.player.physic.speed_max.x = (events.keys[SDL_SCANCODE_LSHIFT] && \
									!events.keys[SDL_SCANCODE_LCTRL]) ? 2 : 1;
	n_game.player.physic.speed_max.y = (events.keys[SDL_SCANCODE_LSHIFT] && \
									!events.keys[SDL_SCANCODE_LCTRL]) ? 2 : 1;
	n_game.player.physic.speed_max.z = game.player.physic.speed_max.z;
	n_game.player.physic.height = (events.keys[SDL_SCANCODE_LCTRL] && \
									!n_game.player.physic.fly) ? 0.5 : 1;
	return (n_game);
}