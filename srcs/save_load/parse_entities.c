/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:47:41 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/18 15:35:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_entity	parse_entities_2(t_c_entity struc_e, t_array *multi_mats)
{
	t_entity current;

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
	if (struc_e.mats != -1)
		current.mat = (t_array *)id_to_p(struc_e.mats, multi_mats,
			sizeof(t_array));
	else
		current.mat = NULL;
	current.damage = struc_e.damage;
	current.life = f_to_float(struc_e.life);
	current.type = (t_entity_type)struc_e.type;
	return (current);
}

t_entity		*parse_entities(void *buf, t_save save, t_array *multi_mats,
size_t n_entities)
{
	t_c_entity	struc_e;
	t_entity	*entities;
	t_entity	current;
	size_t		i;

	entities = (t_entity *)safe_malloc((sizeof(t_entity) * n_entities),
		"loader");
	i = 0;
	while (i < n_entities)
	{
		struc_e = *(t_c_entity *)dump_struct(buf, save.index
			+ sizeof(t_c_entity) * i, sizeof(t_c_entity), save.max);
		verify_magic(&struc_e, ENTITY_MAGIC, i);
		current = parse_entities_2(struc_e, multi_mats);
		entities[i] = current;
		i++;
	}
	return (entities);
}

static t_array	parse_inventory(void *buf, t_save save, t_entity *entities,
size_t n_inventory)
{
	t_array		res;
	size_t		index;
	t_entity	*entity;
	size_t		i;

	res = safe_anew(NULL, 1, sizeof(t_entity *), "loader");
	i = 0;
	while (i < n_inventory)
	{
		index = *(size_t *)dump_struct(buf, save.index + sizeof(size_t) * i,
			sizeof(size_t), save.max);
		entity = id_to_p(index, entities, sizeof(t_entity));
		apush(&res, &entity);
		i++;
	}
	return (res);
}

static t_player	parse_player_2(t_player current, t_c_player struc_p)
{
	current.my_entity.physic.pos = fvec3_to_vec3(struc_p.my_entity.spawn.pos);
	current.my_entity.physic.speed_max = fvec3_to_vec3(struc_p.my_entity.
		spawn.speed_max);
	current.my_entity.physic.look_v = struc_p.my_entity.spawn.look.v;
	current.my_entity.physic.look_h = f_to_float(struc_p.my_entity.spawn.
		look.u);
	if (current.my_entity.physic.look_h > M_PI / 2 && current.my_entity.physic
		.look_h < -M_PI / 2)
		current.my_entity.physic.look_h = 0;
	current.my_entity.physic.sector_id = struc_p.my_entity.spawn.sector_id;
	current.weapons[0] = struc_p.weapons[0];
	current.weapons[1] = struc_p.weapons[1];
	current.secondary = struc_p.secondary;
	current.equiped = struc_p.equiped;
	current.my_entity.damage = struc_p.my_entity.damage;
	return (current);
}

t_player		parse_player(t_c_game game, t_game new_game, void *buf,
t_save save)
{
	t_player	res;
	t_player	current;
	t_c_player	struc_p;

	struc_p = *(t_c_player *)dump_struct(buf, save.index, sizeof(t_c_player),
		save.max);
	verify_magic(&struc_p, PLAYER_MAGIC, 0);
	current = player_default(new_game);
	current.my_entity.physic.gravity = f_to_float(struc_p.my_entity
		.spawn.gravity);
	current.my_entity.physic.height = f_to_float(struc_p.my_entity.spawn
		.height);
	current.my_entity.physic.radius = f_to_float(struc_p.my_entity.spawn
		.radius);
	current.my_entity.physic.rad_inter = f_to_float(struc_p.my_entity.spawn
		.rad_inter);
	save.index = game.loc_inventory;
	current.inventory = parse_inventory(buf, save, new_game.entities,
		game.ninventory);
	current = parse_player_2(current, struc_p);
	res = current;
	return (res);
}
