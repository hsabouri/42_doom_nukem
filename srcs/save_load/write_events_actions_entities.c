/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_events_actions_entities.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:00:11 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/27 15:00:13 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	write_events(int fd, t_plist event)
{
	t_c_game_event	res;
	t_game_event	*current;
	size_t			i;

	i = 0;
	while ((current = (t_game_event *)lpnext(&event)) != NULL)
	{
		res.magic = EVENT_MAGIC + i;
		if (current->trigger.e_actif.id == -1)
			res.trigger.e_actif = -1;
		else
			res.trigger.e_actif = current->trigger.e_actif.id;
		res.trigger.condi = current->trigger.condi;
		if (current->trigger.e_passif.id == -1)
			res.trigger.e_passif = -1;
		else
			res.trigger.e_passif = current->trigger.e_passif.id;
		write_struct(&res, fd, sizeof(t_c_game_event));
		i++;
	}
}

void	write_entities(int fd, t_entity *entities, size_t nentities,
t_array *multi_mats)
{
	t_c_entity	res;
	t_entity	entity;
	size_t		i;

	i = 0;
	while (i < nentities)
	{
		entity = entities[i];
		res = (t_c_entity) {.magic = ENTITY_MAGIC + i, .id = entity.id,
			.spawn.gravity = f_from_float(entity.spawn.gravity),
			.spawn.height = f_from_float(entity.spawn.height),
			.spawn.radius = f_from_float(entity.spawn.radius),
			.spawn.rad_inter = f_from_float(entity.spawn.rad_inter),
			.spawn.pos = vec3_to_fvec3(entity.spawn.pos),
			.spawn.speed_max = vec3_to_fvec3(entity.spawn.speed_max),
			.spawn.look.u = f_from_float(entity.physic.look_h),
			.spawn.look.v = entity.spawn.look_v,
			.spawn.sector_id = entity.spawn.sector_id,
			.type = entity.type, .damage = entity.damage};
		res.mats = (entity.mat != NULL) ? (ssize_t)id_from_p(entity.mat,
			multi_mats, sizeof(t_array)) : -1;
		write_struct(&res, fd, sizeof(t_c_entity));
		i++;
	}
}

void	write_inventory(t_player player, t_entity *entities, int fd)
{
	t_entity	**entity;
	size_t		index;

	index = 0;
	while ((entity = (t_entity **)ashift(&player.inventory)))
	{
		index = id_from_p(*entity, entities, sizeof(t_entity));
		write_struct(&index, fd, sizeof(size_t));
	}
}

void	write_player(t_player player, int fd, t_array *multi_mats)
{
	t_c_player	res;
	u_int32_t	index;

	res.magic = PLAYER_MAGIC;
	res.my_entity.spawn.gravity = f_from_float(player.my_entity.spawn.gravity);
	res.my_entity.spawn.height = f_from_float(player.my_entity.spawn.height);
	res.my_entity.spawn.radius = f_from_float(player.my_entity.spawn.radius);
	res.my_entity.spawn.rad_inter = f_from_float(
		player.my_entity.spawn.rad_inter);
	res.my_entity.spawn.pos = vec3_to_fvec3(player.my_entity.spawn.pos);
	res.my_entity.spawn.speed_max = vec3_to_fvec3(
		player.my_entity.spawn.speed_max);
	res.my_entity.spawn.look.u = f_from_float(player.my_entity.physic.look_h);
	res.my_entity.spawn.look.v = player.my_entity.spawn.look_v;
	res.my_entity.spawn.sector_id = player.my_entity.spawn.sector_id;
	index = id_from_p(player.my_entity.mat, multi_mats, sizeof(t_array));
	res.my_entity.mats = (ssize_t)index;
	res.my_entity.damage = player.my_entity.damage;
	res.life = player.life;
	res.weapons[0] = player.weapons[0];
	res.weapons[1] = player.weapons[1];
	res.secondary = player.secondary;
	res.equiped = player.equiped;
	write_struct(&res, fd, sizeof(t_c_player));
}
