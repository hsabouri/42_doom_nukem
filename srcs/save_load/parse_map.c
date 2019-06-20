/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:06:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/20 10:33:37 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_mat		*parse_mats(void *buf, t_save save, t_img *texture,
size_t nmats)
{
	t_c_mat	struc_m;
	t_mat	*materials;
	t_mat	current;
	size_t	i;

	materials = (t_mat *)safe_malloc((sizeof(t_mat) * nmats), "loader");
	i = -1;
	while (++i < nmats)
	{
		struc_m = *(t_c_mat *)dump_struct(buf, save.index + sizeof(t_c_mat)
			* i, sizeof(t_c_mat), save.max);
		verify_magic(&struc_m, MAT_MAGIC, i);
		current.pos = struc_m.pos;
		current.sca = struc_m.sca;
		current.color = struc_m.color;
		current.mode = struc_m.mode;
		current.filter = struc_m.filter;
		current.frozen = struc_m.frozen;
		current.texture = (struc_m.texture == -1) ? NULL
			: id_to_p(struc_m.texture, texture, sizeof(t_img));
		current.overlay = (struc_m.overlay == -1) ? NULL
			: id_to_p(struc_m.overlay, materials, sizeof(t_mat));
		materials[i] = current;
	}
	return (materials);
}

t_vec2		*parse_points(void *buf, t_save save, size_t npoints)
{
	t_c_point	struc_p;
	t_vec2		*points;
	size_t		i;

	points = (t_vec2 *)safe_malloc((sizeof(t_vec2) * npoints), "loader");
	i = 0;
	while (i < npoints)
	{
		struc_p = *(t_c_point *)dump_struct(buf, save.index
			+ sizeof(t_c_point) * i, sizeof(t_c_point), save.max);
		verify_magic(&struc_p, POINT_MAGIC, i);
		points[i] = fvec2_to_vec2(struc_p.point);
		i++;
	}
	return (points);
}

t_wall		*parse_walls(void *buf, t_save save, t_mat *mats,
size_t nwalls)
{
	t_c_wall	struc_w;
	t_wall		*walls;
	t_wall		current;
	size_t		i;

	walls = (t_wall *)safe_malloc((sizeof(t_wall) * nwalls), "loader");
	i = 0;
	while (i < nwalls)
	{
		struc_w = *(t_c_wall *)dump_struct(buf, save.index
			+ sizeof(t_c_wall) * i, sizeof(t_c_wall), save.max);
		verify_magic(&struc_w, WALL_MAGIC, i);
		current = walls[i];
		current.tex_pos = struc_w.tex_pos;
		current.portal = struc_w.portal;
		current.a = struc_w.a;
		current.b = struc_w.b;
		current.mat = (struc_w.mat == -1) ? NULL : id_to_p(struc_w.mat, mats,
			sizeof(t_mat));
		current.left_z = fvec2_to_vec2(struc_w.left_z);
		current.right_z = fvec2_to_vec2(struc_w.right_z);
		walls[i] = current;
		i++;
	}
	return (walls);
}

t_sector	*parse_sectors(void *buf, t_save save, t_mat *mats,
size_t nsectors)
{
	t_c_sector	struc_s;
	t_sector	*sectors;
	size_t		i;

	sectors = (t_sector *)safe_malloc((sizeof(t_sector) * nsectors), "loader");
	i = -1;
	while (++i < nsectors)
	{
		struc_s = *(t_c_sector *)dump_struct(buf, save.index
			+ sizeof(t_c_sector) * i, sizeof(t_c_sector), save.max);
		verify_magic(&struc_s, SECTOR_MAGIC, i);
		sectors[i] = (t_sector) {.start = struc_s.start,
			.sector_id = struc_s.sector_id, .tex_pos = struc_s.tex_pos,
			.floor = fvec3_to_vec3(struc_s.floor), .ambient = struc_s.ambient,
			.ceiling = fvec3_to_vec3(struc_s.ceiling), .number = struc_s.number,
			.floor_b = fvec3_to_vec3(struc_s.floor_b),
			.ceiling_b = fvec3_to_vec3(struc_s.ceiling_b),
			.ceiling_mat = (struc_s.ceiling_mat == -1) ? NULL
				: id_to_p(struc_s.ceiling_mat, mats, sizeof(t_mat)),
			.floor_mat = (struc_s.floor_mat == -1) ? NULL
				: id_to_p(struc_s.floor_mat, mats, sizeof(t_mat))};
		sectors[i].center = fvec2_to_vec2(struc_s.center);
	}
	return (sectors);
}

t_portal	*parse_portals(void *buf, t_save save, size_t nportals,
t_mat *mats)
{
	t_c_portal	struc_p;
	t_portal	*portals;
	t_portal	current;
	size_t		i;

	portals = (t_portal *)safe_malloc((sizeof(t_portal) * nportals), "loader");
	i = 0;
	while (i < nportals)
	{
		struc_p = *(t_c_portal *)dump_struct(buf, save.index
			+ sizeof(t_c_portal) * i, sizeof(t_c_portal), save.max);
		verify_magic(&struc_p, PORTAL_MAGIC, i);
		current = portals[i];
		current.blocking = struc_p.blocking;
		current.from_sector = struc_p.from_sector;
		current.to_sector = struc_p.to_sector;
		current.from_wall = struc_p.from_wall;
		current.to_wall = struc_p.to_wall;
		current.mat = (struc_p.mat == -1) ? NULL
			: id_to_p(struc_p.mat, mats, sizeof(t_mat));
		portals[i] = current;
		i++;
	}
	return (portals);
}
