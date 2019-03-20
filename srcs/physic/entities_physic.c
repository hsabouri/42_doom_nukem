/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_physic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:43:42 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/01 13:40:08 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec3	z_move(t_ph *physic, t_game game, float old_timer)
{
	t_vec3	new_speed;
	float	delta;
	float	tmp;

	new_speed = physic->speed;
	delta = game.sectors[physic->sector_id].floor - physic->pos.z;
	if (physic->jump && (physic->pos.z > game.sectors[physic->sector_id].floor
		- 0.1 && physic->pos.z < game.sectors[physic->sector_id].floor + 0.1))
	{
		new_speed.z = 0.1;
		physic->jump = 0;
	}
	else if (delta < 0 && !physic->fly && new_speed.z > MAX_FALL)
		new_speed.z -= physic->gravity * old_timer * FALL_MULTIPLY;
	tmp = physic->pos.z + new_speed.z;
	new_speed = floor_col(tmp, game.sectors[physic->sector_id], new_speed);
	tmp = physic->pos.z + physic->height + new_speed.z;
	new_speed = ceil_col(tmp, game.sectors[physic->sector_id], new_speed);
	return (new_speed);
}

static t_vec3	wall_touch(t_touch touch, t_ph *physic, int wall, t_game game)
{
	t_vec3	final_speed;
	t_vec3	next_pos;

	next_pos = touch.pos;
	next_pos = slide_wall(next_pos, game, game.walls[touch.wall]);
	touch = collision(next_pos, *physic, game, wall);
	if (touch.wall != -1)
	{
		final_speed.x = (physic->speed.x - (1 - touch.dist + EPSILON)) *
			physic->speed.x;
		final_speed.y = final_speed.x / physic->speed.x * physic->speed.y;
		final_speed.z = final_speed.x / physic->speed.x * physic->speed.z;
		next_pos = vec3_add(physic->pos, final_speed);
	}
	return (next_pos);
}          

static t_vec3	move_entities(t_ph *physic, t_game game, int wall, float old_timer)
{
	t_vec3	next_pos;
	t_touch	touch;
	t_tp	teleport;

	next_pos = vec3_add(physic->pos, physic->speed);
	physic->speed = z_move(physic, game, old_timer);
	next_pos = vec3_add(physic->pos, physic->speed);
	touch = collision(next_pos, *physic, game, wall);
	if (touch.wall >= 0)
	{
		touch.pos = next_pos;
		if (game.walls[touch.wall].portal == -1)
			return (wall_touch(touch, physic, wall, game));
		else
		{
			set_tp(&teleport, touch, game);
			physic->pos = teleportation(physic->pos, game, teleport, physic);
			return (move_entities(physic, game, teleport.portal_out, old_timer));
		}
		return (next_pos);
	}
	return (next_pos);
}

static t_vec3	col_entities(t_ph n_physic, t_ph physic, t_game game, size_t id)
{
	t_vec3	pos;
	size_t	i;
	float	d;

	i = -1;
	pos = n_physic.pos;
	while (++i < game.nentities)
	{
		d = circle_circle(n_physic, game.entities[i].physic, COL_ENTITY);
		if (d != -1 && i != id)
		{
			game.log[1].e_actif = game.player.my_entity; // Set the player as an entities

			game.log[1].condi = TRIGGER_TOUCH;
			game.log[1].e_passif = game.entities[i];

			if (n_physic.pos.x > game.entities[i].physic.pos.x)
			{
				physic.pos.x += (game.entities[i].physic.radius - d);
				physic.pos.y += (game.entities[i].physic.radius - d);
			}
			else
			{
				physic.pos.x -= (game.entities[i].physic.radius - d);
				physic.pos.y -= (game.entities[i].physic.radius - d);
			}
			pos = vec3_add(physic.pos, physic.speed);
		}
	}
	return (pos);
}

static void		col_interact(t_ph n_physic, t_game game, size_t id)
{
	size_t	cpt;
	size_t	log_inter;

	cpt = 0;
	log_inter = 0;
	while (cpt < game.nentities)
	{
		if (interact(n_physic, game.entities[cpt].physic) == 1 && cpt != id)
			log_inter = cpt; //a remplacer par log des collisions
		cpt++;
	}
}

t_ph			entities_physic(t_ph physic, t_game game, size_t id, float old_timer)
{
	t_ph		n_physic;
	t_last_pos	last_pos;

	n_physic = physic;
	n_physic.pos = move_entities(&n_physic, game, -1, old_timer);
	n_physic.speed.x = 0;
	n_physic.speed.y = 0;
	if ((n_physic.pos.z > game.sectors[n_physic.sector_id].floor - 0.1 &&
		n_physic.pos.z < game.sectors[n_physic.sector_id].floor + 0.1) ||
		n_physic.fly)
	{
		n_physic.speed.z = 0;
		n_physic.jump = 0;
	}
	last_pos.pos = game.player.my_entity.physic.pos;
	last_pos.sector_id = game.player.my_entity.physic.sector_id;
	n_physic.pos = col_entities(n_physic, physic, game, id);
	n_physic = entities_track(n_physic, game, last_pos);
	col_interact(n_physic, game, id);
	return (n_physic);
}
