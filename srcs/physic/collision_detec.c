/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:18:50 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/28 15:18:51 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static void	slide_entity(t_ph n_physic, t_game *game, t_ph physic, size_t i,
float d)
{
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
}

t_vec3		col_entities(t_ph n_physic, t_ph physic, t_game *game, size_t id)
{
	t_trigger	tmp_log;
	t_vec3		pos;
	size_t		i;
	float		d;

	i = -1;
	pos = n_physic.pos;
	while (++i < game->nentities)
	{
		d = circle_circle(n_physic, game->entities[i].physic, COL_ENTITY);
		if (d != -1 && i != id)
		{
			tmp_log.e_actif = game->player.my_entity;
			tmp_log.condi = TRIGGER_TOUCH;
			tmp_log.e_passif = game->entities[i];
			apush(&game->log, &tmp_log);
			slide_entity(n_physic, game, physic, i, d);
			pos = vec3_add(physic.pos, physic.speed);
		}
	}
	return (pos);
}

void		col_interact(t_ph n_physic, t_game *game, size_t id)
{
	t_trigger	tmp_log;
	size_t		cpt;
	size_t		log_inter;

	cpt = 0;
	log_inter = 0;
	while (cpt < game->nentities)
	{
		if (interact(n_physic, game->entities[cpt].physic) == 1 && cpt != id)
		{
			tmp_log.e_actif = game->player.my_entity;
			tmp_log.condi = TRIGGER_INTERACT;
			tmp_log.e_passif = game->entities[cpt];
			apush(&game->log, &tmp_log);
		}
		cpt++;
	}
}
