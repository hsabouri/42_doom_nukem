/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_sounds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:10:02 by iporsenn          #+#    #+#             */
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
