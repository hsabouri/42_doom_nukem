/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:06:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/19 16:06:51 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_mat		*parse_mats(void *buf, t_save save, t_img *texture,\
size_t n_entities)
{
	t_c_mat	struc_m;
	t_mat	*materials;
	t_mat	current;
	size_t	i;

	materials = (t_mat *)malloc(sizeof(t_mat) * n_entities);
	i = -1;
	while (++i < n_entities)
	{
		struc_m = *(t_c_mat *)dump_struct(buf, save.index + sizeof(t_c_mat) *
			i, sizeof(t_c_mat), save.max);
		verify_magic(&struc_m, MAT_MAGIC, i);
		current = materials[i];
		current.pos = struc_m.pos;
		current.sca = struc_m.sca;
		current.color = struc_m.color;
		current.mode = struc_m.mode;
		current.filter = struc_m.filter;
		current.texture = (struc_m.texture == -1) ? NULL :
			id_to_p(struc_m.texture, texture, sizeof(t_img));
		current.overlay = (struc_m.overlay == -1) ? NULL :
			id_to_p(struc_m.overlay, materials, sizeof(t_mat));
		materials[i] = current;
	}
	return (materials);
}

t_vec2		*parse_points(void *buf, t_save save, size_t n_entities)
{
	t_c_point	struc_p;
	t_vec2		*points;
	size_t		i;

	points = (t_vec2 *)malloc(sizeof(t_vec2) * n_entities);
	i = 0;
	while (i < n_entities)
	{
		struc_p = *(t_c_point *)dump_struct(buf, save.index +
			sizeof(t_c_point) * i, sizeof(t_c_point), save.max);
		verify_magic(&struc_p, POINT_MAGIC, i);
		points[i] = fvec2_to_vec2(struc_p.point);
		i++;
	}
	return (points);
}

t_wall		*parse_walls(void *buf, t_save save, t_mat *mats,\
size_t n_entities)
{
	t_c_wall	struc_w;
	t_wall		*walls;
	t_wall		current;
	size_t		i;

	walls = (t_wall *)malloc(sizeof(t_wall) * n_entities);
	i = 0;
	while (i < n_entities)
	{
		struc_w = *(t_c_wall *)dump_struct(buf, save.index +
			sizeof(t_c_wall) * i, sizeof(t_c_wall), save.max);
		verify_magic(&struc_w, WALL_MAGIC, i);
		current = walls[i];
		current.tex_pos = struc_w.tex_pos;
		current.portal = struc_w.portal;
		current.a = struc_w.a;
		current.b = struc_w.b;
		current.mat = id_to_p((ssize_t)struc_w.mat, mats, sizeof(t_mat));
		walls[i] = current;
		i++;
	}
	return (walls);
}

t_sector	*parse_sectors(void *buf, t_save save, t_mat *mats,\
size_t n_entities)
{
	t_c_sector	struc_s;
	t_sector	*sectors;
	t_sector	current;
	size_t		i;

	sectors = (t_sector *)malloc(sizeof(t_sector) * n_entities);
	i = -1;
	while (++i < n_entities)
	{
		struc_s = *(t_c_sector *)dump_struct(buf, save.index +
			sizeof(t_c_sector) * i, sizeof(t_c_sector), save.max);
		verify_magic(&struc_s, SECTOR_MAGIC, i);
		current = sectors[i];
		current = (t_sector) {.start = struc_s.start, .number = struc_s.number,
			.sector_id = struc_s.sector_id,
			.floor = f_to_float(struc_s.floor),
			.ceiling = f_to_float(struc_s.ceiling),
			.ambient = struc_s.ambient,
			.ceiling_mat = id_to_p((ssize_t)struc_s.ceiling_mat,
				mats, sizeof(t_mat)),
			.floor_mat = id_to_p((ssize_t)struc_s.floor_mat, mats,
				sizeof(t_mat))};
		sectors[i] = current;
	}
	return (sectors);
}

t_portal	*parse_portals(void *buf, t_save save, size_t n_entities)
{
	t_c_portal	struc_p;
	t_portal	*portals;
	t_portal	current;
	size_t		i;

	portals = (t_portal *)malloc(sizeof(t_portal) * n_entities);
	i = 0;
	while (i < n_entities)
	{
		struc_p = *(t_c_portal *)dump_struct(buf, save.index +
			sizeof(t_c_portal) * i, sizeof(t_c_portal), save.max);
		verify_magic(&struc_p, PORTAL_MAGIC, i);
		current = portals[i];
		current.from_sector = struc_p.from_sector;
		current.to_sector = struc_p.to_sector;
		current.from_wall = struc_p.from_wall;
		current.to_wall = struc_p.to_wall;
		current.a = struc_p.a;
		current.b = struc_p.b;
		portals[i] = current;
		i++;
	}
	return (portals);
}
