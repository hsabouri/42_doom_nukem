/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_textures_musics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:25:46 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/05 16:45:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

size_t				write_textures(int fd, t_img *textures, size_t ntextures,
int index)
{
	t_c_img	s_textures;
	size_t	i;
	size_t	loc_content;

	i = 0;
	loc_content = 0;
	while (i < ntextures)
	{
		s_textures.magic = TEXT_MAGIC + i;
		s_textures.width = textures[i].width;
		s_textures.height = textures[i].height;
		if (i == 0)
			loc_content = (size_t)index;
		else
			loc_content += (size_t)(textures[i - 1].width
				* textures[i - 1].height) * sizeof(t_color);
		s_textures.content = loc_content;
		s_textures.edit = textures[i].edit;
		write_struct(&s_textures, fd, sizeof(t_c_img));
		i++;
	}
	loc_content += (size_t)(textures[i - 1].width * textures[i - 1].height)
		* sizeof(t_color);
	return (loc_content);
}
