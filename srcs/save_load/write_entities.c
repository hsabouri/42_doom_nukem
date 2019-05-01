/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:13:57 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/01 16:23:26 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	write_entities(int fd, t_entity *entities, size_t nentities,\
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
		res.id = entity.id;
		res.spawn.gravity = f_from_float(entity.spawn.gravity);
		res.spawn.height = f_from_float(entity.spawn.height);
		res.spawn.radius = f_from_float(entity.spawn.radius);
		res.spawn.rad_inter = f_from_float(entity.spawn.rad_inter);
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

void	write_weapons(int fd, t_weapon *weapons, size_t nentities,\
t_img *textures)
{
	t_c_weapon	res;
	t_weapon	gun;
	t_img		**material;
	u_int32_t	index;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < nentities)
	{
		gun = weapons[i];
		res.magic = GUN_MAGIC + i;
		res.name = gun.name;
		res.type = gun.type;
		res.ammo = gun.ammo;
		res.ammo_max = gun.ammo_max;
		res.damage = gun.damage;
		res.cadence = gun.cadence;
		res.type_shot = gun.type_shot;
		j = 0;
		while ((material = (t_img **)ashift(&gun.sprite)))
		{
			index = id_from_p(*material, textures, sizeof(t_img));
			res.sprite[j] = (ssize_t)index;
			j++;
		}
		while (j < 16)
		{
			res.sprite[j] = -1;
			j++;
		}
		res.decal = gun.decal;
		write_struct(&res, fd, sizeof(t_c_weapon));
		i++;
	}
}