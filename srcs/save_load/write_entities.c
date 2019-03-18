/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:13:57 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/07 17:13:59 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	translate_entity(int fd, t_entity *entities, size_t nentities,\
t_mat *mats)
{
	t_c_entity	res;
	size_t		i;

	i = 0;
	while (i < nentities)
	{
		res.magic = ENTITY_MAGIC + i;
		res.spawn.gravity = f_from_float(entities[i].spawn.gravity);
		res.spawn.height = f_from_float(entities[i].spawn.height);
		res.spawn.radius = f_from_float(entities[i].spawn.radius);
		res.spawn.pos = vec3_to_fvec3(entities[i].spawn.pos);
		res.spawn.speed_max = vec3_to_fvec3(entities[i].spawn.speed_max);
		res.spawn.look.u = f_from_float(entities[i].physic.look_h);
		res.spawn.look.v = entities[i].spawn.look_v;
		res.spawn.sector_id = entities[i].spawn.sector_id;
		res.mat = id_from_p(entities[i].mat, mats, sizeof(t_mat));
		res.damage = entities[i].damage;
		write_struct(&res, fd, sizeof(t_c_entity));
		i++;
	}
}
