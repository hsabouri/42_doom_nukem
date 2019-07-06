/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:55:23 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 13:22:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

int		is_shooting(t_game *game, t_player player, t_event events,
size_t frame)
{
	static size_t	last = 0;
	const t_weapon	weapon = game->weapons[player.weapons[player.equiped]];

	if (frame - last > weapon.cadence && events.mouse[SDL_BUTTON_LEFT])
	{
		last = frame;
		if (weapon.ammo == 0)
		{
			game->chunks = stack_sounds(game->chunks, 3, 0.5);
			return (0);
		}
		return (1);
	}
	else
		return (0);
}

t_game	shooting_sound(t_game game)
{
	const t_player	player = game.player;
	const t_weapon	weapon = game.weapons[player.weapons[player.equiped]];

	if (weapon.name == W_GUN)
		game.chunks = stack_sounds(game.chunks, 6, 0.5);
	else if (weapon.name == W_SMG)
		game.chunks = stack_sounds(game.chunks, 7, 0.5);
	else if (weapon.name == W_SHOTGUN)
		game.chunks = stack_sounds(game.chunks, 8, 0.5);
	else if (weapon.name == W_REVOLVER)
		game.chunks = stack_sounds(game.chunks, 9, 0.5);
	else if (weapon.name == W_NYAN_GUN)
		game.chunks = stack_sounds(game.chunks, 10, 0.5);
	return (game);
}
