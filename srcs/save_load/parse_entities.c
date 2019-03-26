/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:47:41 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/19 16:20:41 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_entity		*parse_entities(void *buf, t_save save, t_mat *mats,\
size_t n_entities)
{
	t_c_entity	struc_e;
	t_entity	*entities;
	t_entity	current;
	size_t		i;

	entities = (t_entity *)malloc(sizeof(t_entity) * n_entities);
	i = 0;
	while (i < n_entities)
	{
		struc_e = *(t_c_entity *)dump_struct(buf, save.index +
			sizeof(t_c_entity) * i, sizeof(t_c_entity), save.max);
		verify_magic(&struc_e, ENTITY_MAGIC, i);
		current = entity_default();
		current.physic.gravity = f_to_float(struc_e.spawn.gravity);
		current.physic.height = f_to_float(struc_e.spawn.height);
		current.physic.radius = f_to_float(struc_e.spawn.radius);
		current.physic.pos = fvec3_to_vec3(struc_e.spawn.pos);
		current.physic.speed_max = fvec3_to_vec3(struc_e.spawn.speed_max);
		current.physic.look_v = struc_e.spawn.look.v;
		current.physic.look_h = f_to_float(struc_e.spawn.look.u);
		if (current.physic.look_h > M_PI / 2 && current.physic.look_h < -M_PI / 2)
			current.physic.look_h = 0;
		current.physic.sector_id = struc_e.spawn.sector_id;
		//current.mat = id_to_p((ssize_t)struc_e.mat, mats, sizeof(t_mat));
		current.mat = anew(NULL, 0, sizeof(t_mat *));
		current.damage = struc_e.damage;
		entities[i] = current;
		i++;
	}
	return (entities);
}
