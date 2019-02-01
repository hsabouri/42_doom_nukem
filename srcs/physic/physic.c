/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:57:34 by iporsenn          #+#    #+#             */
/*   Updated: 2018/12/21 17:57:35 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	physic(t_game game, t_event events)
{
	t_game		new_game;
	t_last_pos	last_pos;

	new_game = game;
	last_pos.pos = game.player.physic.pos;
	last_pos.sector_id = game.player.physic.sector_id;
	new_game.player = player_physic(events, game);
	new_game.player = player_track(new_game.player, game, last_pos);
	return (new_game);
}
