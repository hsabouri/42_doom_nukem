/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_physic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:43:42 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/18 13:51:43 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec3	z_move(t_ph *physic, t_game game, float old_timer)
{
	t_vec3	new_speed;
	float	delta;
	t_vec3	tmp;

	new_speed = physic->speed;
	delta = game.sectors[physic->sector_id].floor.z - physic->pos.z;
	if (physic->jump && (physic->pos.z > game.sectors[physic->sector_id].floor.z
		- 0.1 && physic->pos.z < game.sectors[physic->sector_id].floor.z + 0.1))
	{
		new_speed.z = 0.13;
	}
	else if (delta < 0 && !physic->fly && new_speed.z > MAX_FALL)
		new_speed.z -= physic->gravity * old_timer * FALL_MULTIPLY;
	tmp = vec3_add(physic->pos, new_speed);
	new_speed = floor_col(tmp.z, game.sectors[physic->sector_id], new_speed,
		&physic->jump);
	tmp = vec3_add(physic->pos, new_speed);
	tmp.z = tmp.z + physic->height;
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
		final_speed.x = (physic->speed.x - (1 - touch.dist + EPSILON))
			* physic->speed.x;
		final_speed.y = final_speed.x / physic->speed.x * physic->speed.y;
		final_speed.z = final_speed.x / physic->speed.x * physic->speed.z;
		next_pos = vec3_add(physic->pos, final_speed);
	}
	return (next_pos);
}

static t_vec3	move_entities(t_ph *physic, t_game *game, int wall,
float old_timer)
{
	t_vec3	next_pos;
	t_touch	touch;
	t_tp	teleport;
	float	inter;

	next_pos = vec3_add(physic->pos, physic->speed);
	inter = (z_inter(game->sectors[physic->sector_id], next_pos, 0)
		- z_inter(game->sectors[physic->sector_id], next_pos, 1));
	if (inter < physic->height + 0.5)
		return (physic->pos);
	physic->speed = z_move(physic, *game, old_timer);
	next_pos = vec3_add(physic->pos, physic->speed);
	touch = collision(next_pos, *physic, *game, wall);
	if (touch.wall >= 0)
	{
		touch.pos = next_pos;
		if (game->walls[touch.wall].portal == -1
			|| (game->walls[touch.wall].portal != -1
			&& game->portals[game->walls[touch.wall].portal].blocking == 1))
			return (wall_touch(touch, physic, wall, *game));
		else
		{
			set_tp(&teleport, touch, *game);
			physic->pos = teleportation(physic->pos, game, teleport, physic);
			return (move_entities(physic, game, teleport.portal_out,
				old_timer));
		}
		return (next_pos);
	}
	return (next_pos);
}

t_ph			entities_physic(t_ph physic, t_game *game, ssize_t id,
float old_timer)
{
	t_ph		n_physic;
	t_last_pos	last_pos;

	n_physic = physic;
	n_physic.pos = move_entities(&n_physic, game, -1, old_timer);
	n_physic.speed.x = 0;
	n_physic.speed.y = 0;
	if ((n_physic.pos.z > game->sectors[n_physic.sector_id].floor.z - 0.1
		&& n_physic.pos.z < game->sectors[n_physic.sector_id].floor.z + 0.1)
		|| n_physic.fly)
	{
		n_physic.speed.z = 0;
		n_physic.jump = 0;
	}
	last_pos.pos = game->player.my_entity.physic.pos;
	last_pos.sector_id = game->player.my_entity.physic.sector_id;
	if (id < 0)
		n_physic.pos = col_entities(n_physic, physic, game, id);
	n_physic = entities_track(n_physic, *game, last_pos);
	if (id < 0)
		col_interact(n_physic, game, id);
	return (n_physic);
}
