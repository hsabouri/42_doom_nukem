/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:47:41 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/01 16:23:12 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_entity		*parse_entities(void *buf, t_save save, t_mat *mats,\
size_t n_entities)
{
	t_c_entity	struc_e;
	t_entity	*entities;
	t_entity	current;
	t_mat		*mat;
	size_t		i;
	size_t		j;

	entities = (t_entity *)safe_malloc((sizeof(t_entity) * n_entities), "loader");
	i = 0;
	while (i < n_entities)
	{
		struc_e = *(t_c_entity *)dump_struct(buf, save.index +
			sizeof(t_c_entity) * i, sizeof(t_c_entity), save.max);
		verify_magic(&struc_e, ENTITY_MAGIC, i);
		current = entity_default();
		current.id = struc_e.id;
		current.physic.gravity = f_to_float(struc_e.spawn.gravity);
		current.physic.height = f_to_float(struc_e.spawn.height);
		current.physic.radius = f_to_float(struc_e.spawn.radius);
		current.physic.rad_inter = f_to_float(struc_e.spawn.rad_inter);
		current.physic.pos = fvec3_to_vec3(struc_e.spawn.pos);
		current.physic.speed_max = fvec3_to_vec3(struc_e.spawn.speed_max);
		current.physic.look_v = struc_e.spawn.look.v;
		current.physic.look_h = f_to_float(struc_e.spawn.look.u);
		if (current.physic.look_h > M_PI / 2 && current.physic.look_h < -M_PI / 2)
			current.physic.look_h = 0;
		current.physic.sector_id = struc_e.spawn.sector_id;
		current.mat = safe_anew(NULL, 1, sizeof(t_mat *), "loader");
		j = 0;
		while (j < 16)
		{
			mat = (struc_e.mat[j] == -1) ? NULL : 
				id_to_p(struc_e.mat[j], mats, sizeof(t_mat));
			if (!mat)
				break;
			else
				apush(&current.mat, &mat);
			j++;
		}
		current.damage = struc_e.damage;
		entities[i] = current;
		i++;
	}
	return (entities);
}

t_weapon		*parse_weapons(void *buf, t_save save, t_img *textures,\
size_t n_weapons)
{
	t_c_weapon	struc_w;
	t_weapon	*weapons;
	t_weapon	current;
	t_img		*mat;
	size_t		i;
	size_t		j;

	weapons = (t_weapon *)safe_malloc((sizeof(t_weapon) * n_weapons), "loader");
	i = 0;
	while (i < n_weapons)
	{
		struc_w = *(t_c_weapon *)dump_struct(buf, save.index +
			sizeof(t_c_weapon) * i, sizeof(t_c_weapon), save.max);
		verify_magic(&struc_w, GUN_MAGIC, i);
		current.name = struc_w.name;
		current.type = struc_w.type;
		current.ammo = struc_w.ammo;
		current.ammo_max = struc_w.ammo_max;
		current.damage = struc_w.damage;
		current.cadence = struc_w.cadence;
		current.type_shot = struc_w.type_shot;
		current.sprite = safe_anew(NULL, 1, sizeof(t_img *), "loader");
		j = 0;
		while (j < 16)
		{
			mat = (struc_w.sprite[j] == -1) ? NULL : 
				(t_img *)(id_to_p(struc_w.sprite[j], textures, sizeof(t_img)));
			if (!mat)
				break;
			else
				apush(&current.sprite, &mat);
			j++;
		}
		current.decal = struc_w.decal;
		weapons[i] = current;
		i++;
	}
	return (weapons);
}