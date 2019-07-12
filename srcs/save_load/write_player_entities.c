/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_player_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:00:11 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/12 10:30:03 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	write_entities(int fd, t_entity *entities, size_t nentities,
t_array *multi_mats)
{
	t_c_entity	res;
	t_entity	e;
	size_t		i;

	i = 0;
	while (i < nentities)
	{
		e = entities[i];
		res = (t_c_entity) {.magic = ENTITY_MAGIC + i, .id = e.id,
			.spawn.gravity = f_from_float(e.spawn.gravity),
			.spawn.height = f_from_float(e.spawn.height),
			.spawn.radius = f_from_float(e.spawn.radius),
			.spawn.rad_inter = f_from_float(e.spawn.rad_inter),
			.spawn.pos = vec3_to_fvec3(e.physic.pos),
			.spawn.speed_max = vec3_to_fvec3(e.spawn.speed_max),
			.spawn.look.u = f_from_float(e.physic.look_h),
			.spawn.look.v = e.spawn.look_v,
			.spawn.sector_id = e.spawn.sector_id,
			.type = e.type, .life = f_from_float(e.life),
			.data = e.data};
		res.mats = (e.mat != NULL) ? (ssize_t)id_from_p(e.mat,
			multi_mats, sizeof(t_array)) : -1;
		write_struct(&res, fd, sizeof(t_c_entity));
		i++;
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
	res.my_entity.data = player.my_entity.data;
	res.weapons[0] = player.weapons[0];
	res.weapons[1] = player.weapons[1];
	res.secondary = player.secondary;
	res.equiped = player.equiped;
	write_struct(&res, fd, sizeof(t_c_player));
}
