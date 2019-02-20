/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_sounds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:10:02 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/19 17:10:05 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

t_img		*parse_textures(void *buf, t_save save, size_t n_entities)
{
	t_c_img		struc_i;
	t_img		*textures;
	t_img		current;
	size_t		i;

	i = 0;
	textures = (t_img *)malloc(sizeof(t_img) * n_entities);
	while (i < n_entities)
	{
		struc_i = *(t_c_img *)dump_struct(buf, save.index +
			sizeof(t_c_img) * i, sizeof(t_c_img), save.max);
		verify_magic(&struc_i, TEXT_MAGIC, i);
		current = textures[i];
		current.width = struc_i.width;
		current.height = struc_i.height;
		current.content = (t_color *)malloc(sizeof(t_color) * current.width *
			current.height);
		ft_memmove(current.content, buf + struc_i.content, sizeof(t_color) *
			current.width * current.height);
		textures[i] = current;
		i++;
	}
	return (textures);
}
