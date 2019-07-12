/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_sounds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:38:40 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/10 14:00:51 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_img		*parse_textures(void *buf, t_save save, size_t ntextures)
{
	t_c_img		struc_i;
	t_img		*textures;
	t_img		current;
	size_t		i;

	i = 0;
	textures = (t_img *)safe_malloc((sizeof(t_img) * ntextures), "loader");
	while (i < ntextures)
	{
		struc_i = *(t_c_img *)dump_struct(buf, save.index + i
			* sizeof(t_c_img), sizeof(t_c_img), save.max);
		verify_magic(&struc_i, TEXT_MAGIC, i);
		current = textures[i];
		current.width = struc_i.width;
		current.height = struc_i.height;
		current.content = (t_color *)safe_malloc((sizeof(t_color)
			* current.width * current.height), "loader");
		ft_memmove(current.content, buf + struc_i.content, sizeof(t_color)
			* current.width * current.height);
		current.edit = struc_i.edit;
		textures[i] = current;
		i++;
	}
	return (textures);
}

t_entity	*fix_fly(t_entity *entities, size_t nentities, t_sector *sectors)
{
	size_t	i;

	i = 0;
	while (i < nentities)
	{
		if (entities[i].physic.pos.z > sectors
			[entities[i].physic.sector_id].floor.z)
			entities[i].physic.fly = 1;
		i++;
	}
	return (entities);
}
