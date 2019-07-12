/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:18:50 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/23 18:01:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_ph	slide_entity(t_ph n_physic, t_game *game, t_ph physic, size_t i)
{
	float d;

	d = circle_circle(n_physic, game->entities[i].physic, COL_ENTITY);
	if (n_physic.pos.x > game->entities[i].physic.pos.x)
	{
		physic.pos.x += (game->entities[i].physic.radius - d);
		physic.pos.y += (game->entities[i].physic.radius - d);
	}
	else
	{
		physic.pos.x -= (game->entities[i].physic.radius - d);
		physic.pos.y -= (game->entities[i].physic.radius - d);
	}
	return (physic);
}

t_vec3		col_entities(t_ph n_physic, t_ph physic, t_game *game, size_t id)
{
	t_vec3		pos;
	size_t		i;
	t_col_event	tmp;
	float		d;

	i = 0;
	pos = n_physic.pos;
	while (i < game->nentities)
	{
		d = circle_circle(n_physic, game->entities[i].physic, COL_ENTITY);
		if (d != -1 && i != id)
		{
			tmp.type = DIRECT;
			tmp.e_id = i;
			apush(&game->col_events, &tmp);
			physic = slide_entity(n_physic, game, physic, i);
			pos = vec3_add(physic.pos, physic.speed);
		}
		i++;
	}
	return (pos);
}

void		col_interact(t_ph n_physic, t_game *game, size_t id)
{
	size_t		cpt;
	size_t		log_inter;
	t_col_event	tmp;

	cpt = 0;
	log_inter = 0;
	while (cpt < game->nentities)
	{
		if (interact(n_physic, game->entities[cpt].physic) == 1 && cpt != id)
		{
			tmp.type = INTERACT;
			tmp.e_id = cpt;
			apush(&game->col_events, &tmp);
		}
		cpt++;
	}
}
