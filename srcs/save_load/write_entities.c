/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:13:57 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/19 16:21:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	translate_entity(int fd, t_entity *entities, size_t nentities,\
t_mat *mats)
{
	t_c_entity	res;
	t_entity	entity;
	t_mat		**material;
	u_int32_t	index;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < nentities)
	{
		entity = entities[i];
		res.magic = ENTITY_MAGIC + i;
		res.spawn.gravity = f_from_float(entity.spawn.gravity);
		res.spawn.height = f_from_float(entity.spawn.height);
		res.spawn.radius = f_from_float(entity.spawn.radius);
		res.spawn.pos = vec3_to_fvec3(entity.spawn.pos);
		res.spawn.speed_max = vec3_to_fvec3(entity.spawn.speed_max);
		res.spawn.look.u = f_from_float(entity.physic.look_h);
		res.spawn.look.v = entity.spawn.look_v;
		res.spawn.sector_id = entity.spawn.sector_id;
		j = 0;
		while ((material = (t_mat **)ashift(&entity.mat)))
		{
			index = id_from_p(*material, mats, sizeof(t_mat));
			res.mat[j] = (ssize_t)index;
			j++;
		}
		while (j < 16)
		{
			res.mat[j] = -1;
			j++;
		}
		res.damage = entity.damage;
		write_struct(&res, fd, sizeof(t_c_entity));
		i++;
	}
}