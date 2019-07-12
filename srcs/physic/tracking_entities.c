/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_entities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:00:05 by iporsenn          #+#    #+#             */
/*   Updated: 2019/01/31 18:00:07 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

u_int32_t			is_in_sector(t_ph physic, t_game game, u_int32_t sector_id)
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
		if (seg_seg(i_pos, physic, &touch, game) == 1)
			nb_inter++;
		touch.wall++;
	}
	return (nb_inter);
}

static t_ph			check_next_sector(t_ph physic, t_game game, u_int32_t cpt,
t_last_pos last_pos)
{
	t_ph		n_physic;
	u_int32_t	portal_out;
	u_int32_t	end;

	n_physic = physic;
	end = game.sectors[physic.sector_id].start
		+ game.sectors[physic.sector_id].number;
	while (cpt < end)
	{
		if (game.walls[cpt].portal != -1)
		{
			portal_out = (game.portals[game.walls[cpt].portal].to_wall == cpt)
				? game.portals[game.walls[cpt].portal].from_sector
				: game.portals[game.walls[cpt].portal].to_sector;
			if ((is_in_sector(physic, game, portal_out) % 2) != 0)
			{
				n_physic.sector_id = portal_out;
				return (n_physic);
			}
		}
		cpt++;
	}
	n_physic.pos = last_pos.pos;
	n_physic.sector_id = last_pos.sector_id;
	return (n_physic);
}

t_ph				entities_track(t_ph physic, t_game game,
t_last_pos last_pos)
{
	u_int32_t	cpt;
	float		inter;

	inter = (z_inter(game.sectors[physic.sector_id], physic.pos, 0)
		- z_inter(game.sectors[physic.sector_id], physic.pos, 1));
	if (inter < physic.height + 0.5)
	{
		physic.pos = last_pos.pos;
		physic.sector_id = last_pos.sector_id;
		physic.pos.z = z_inter(game.sectors[physic.sector_id], physic.pos, 0);
		return (physic);
	}
	if ((is_in_sector(physic, game, physic.sector_id) % 2) != 0)
		return (physic);
	else
	{
		cpt = game.sectors[physic.sector_id].start;
		return (check_next_sector(physic, game, cpt, last_pos));
	}
	return (physic);
}
