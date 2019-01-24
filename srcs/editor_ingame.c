/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ingame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:01:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/24 15:00:22 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game		game_editing(t_game game, t_event events, t_player player)
{
	t_sector *sector;

	sector = &game.sectors[player.physic.sector_id];
	if (game.player.physic.look_v >= 0 && events.keys[SDL_SCANCODE_KP_PLUS])
		*sector = sector_height(game, *sector, PART_CEILING, 0.1);
	if (game.player.physic.look_v >= 0 && events.keys[SDL_SCANCODE_KP_MINUS])
		*sector = sector_height(game, *sector, PART_CEILING, -0.1);
	if (game.player.physic.look_v < 0 && events.keys[SDL_SCANCODE_KP_PLUS])
		*sector = sector_height(game, *sector, PART_FLOOR, 0.1);
	if (game.player.physic.look_v < 0 && events.keys[SDL_SCANCODE_KP_MINUS])
		*sector = sector_height(game, *sector, PART_FLOOR, -0.1);
	return (game);
}
