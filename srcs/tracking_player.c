/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:00:05 by iporsenn          #+#    #+#             */
/*   Updated: 2019/01/31 18:00:07 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

u_int32_t		is_in_sector(t_player player, t_game game, u_int32_t sector_id)
{
	u_int32_t	nb_inter;
	t_touch		touch;
	int			end;
	t_vec3		i_pos;

	nb_inter = 0;
	touch.wall = game.sectors[sector_id].start;
	touch.dist = 0;
	end = game.sectors[sector_id].start + game.sectors[sector_id].number;
	i_pos.x = (10000);
	i_pos.y = (10000);
	i_pos.z = (0);
	while (touch.wall < end)
	{
		if (seg_seg(i_pos, player, &touch, game) == 1)
			nb_inter++;
		touch.wall++;
	}
	return (nb_inter);
}

t_player	player_track(t_player player, t_game game, t_last_pos last_pos)
{
	t_player	n_player;
	u_int32_t	cpt;
	u_int32_t	end;
	u_int32_t	portal_out;

	if ((is_in_sector(player, game, player.physic.sector_id) % 2) != 0)
		return (player);
	else
	{
		n_player = player;
		cpt = game.sectors[player.physic.sector_id].start;
		end = game.sectors[player.physic.sector_id].start + \
				game.sectors[player.physic.sector_id].number;
		while (cpt < end)
		{
			if (game.walls[cpt].portal != -1)
			{
				portal_out = (game.portals[game.walls[cpt].portal].to_wall == \
						cpt) ? game.portals[game.walls[cpt].portal].from_sector :\
						game.portals[game.walls[cpt].portal].to_sector;
				if ((is_in_sector(player, game, portal_out) % 2) != 0)
				{
					n_player.physic.sector_id = portal_out;
					return (n_player);
				}
			}
			cpt++;
		}
		n_player.physic.pos = last_pos.pos;
		n_player.physic.sector_id = last_pos.sector_id;
		return (n_player);
	}
	return (player);
}
