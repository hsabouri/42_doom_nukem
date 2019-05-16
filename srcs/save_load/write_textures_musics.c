/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_textures_musics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:25:46 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/16 15:58:35 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void				write_multi_sprite(int fd, t_array *multi_mats,\
size_t nmulti_mats, t_mat *mats)
{
	size_t			i;
	size_t			j;
	u_int32_t		index;
	t_c_multi_mats	s_multi;
	t_mat			**material;

	i = 0;
	while (i < nmulti_mats)
	{
		j = 0;
		s_multi.magic = MULTI_MAGIC + i;
		while ((material = (t_mat **)anth(&multi_mats[i], j)))
		{
			index = id_from_p(*material, mats, sizeof(t_mat));
			s_multi.mat[j] = (ssize_t)index;
			j++;
		}
		while (j < 16)
		{
			s_multi.mat[j] = -1;
			j++;
		}
		write_struct(&s_multi, fd, sizeof(t_c_multi_mats));
		i++;
	}
}

size_t				write_textures(int fd, t_img *textures, size_t ntextures,\
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
			loc_content += (size_t)(textures[i - 1].width *
				textures[i - 1].height) * sizeof(t_color);
		s_textures.content = loc_content;
		write_struct(&s_textures, fd, sizeof(t_c_img));
		i++;
	}
	loc_content += (size_t)(textures[i - 1].width * textures[i - 1].height) *
		sizeof(t_color);
	return (loc_content);
}

static t_c_music	set_fmusic(t_save_music *music, size_t i, t_audio type)
{
	t_c_music fmusic;

	music->path = (char *)safe_malloc((sizeof(char) * (15 +
		ft_strlen(music->read->d_name))), "saver");
	music->path = (type == MUSIC) ? ft_strcpy(music->path, "./audio/music/") :
		ft_strcpy(music->path, "./audio/sound/");
	music->path = ft_strcat(music->path, music->read->d_name);
	music->file = dump_file(music->path, 0, &music->size);
	music->loc_content += (i == 0) ? 0 : music->old_size;
	ft_strdel(&music->path);
	music->old_size = music->size;
	fmusic.magic = (type == MUSIC) ? MUSIC_MAGIC + i : SOUND_MAGIC + i;
	fmusic.length = music->size;
	fmusic.content = music->loc_content;
	return (fmusic);
}

size_t				write_audio(int fd, int index, t_audio type)
{
	t_c_music		fmusic;
	size_t			i;
	t_save_music	music;

	i = 0;
	music.loc_content = (size_t)index;
	music.old_size = 0;
	music.size = 0;
	music.drt = (type == MUSIC) ? opendir("./audio/music") :
		opendir("./audio/sound");
	while ((music.read = readdir(music.drt)))
	{
		if (ft_strcmp(music.read->d_name, ".") != 0 &&
			ft_strcmp(music.read->d_name, "..") && music.read->d_type == 8 &&
			(ft_strcmp(ft_strrchr(music.read->d_name, '.'), ".ogg") == 0))
		{
			fmusic = set_fmusic(&music, i, type);
			write_struct(&fmusic, fd, sizeof(t_c_music));
			i++;
		}
	}
	closedir(music.drt);
	music.loc_content += music.size;
	return (music.loc_content);
}

void				write_music(int fd, t_audio type)
{
	t_save_music	music;

	music.drt = (type == MUSIC) ? opendir("./audio/music") :
		opendir("./audio/sound");
	while ((music.read = readdir(music.drt)))
	{
		if (ft_strcmp(music.read->d_name, ".") != 0 &&
			ft_strcmp(music.read->d_name, "..") && music.read->d_type == 8 &&
			(ft_strcmp(ft_strrchr(music.read->d_name, '.'), ".ogg") == 0))
		{
			music.path = (char *)safe_malloc((sizeof(char) * (15 +
				ft_strlen(music.read->d_name))), "saver");
			music.path = (type == MUSIC) ?
				ft_strcpy(music.path, "./audio/music/") :
				ft_strcpy(music.path, "./audio/sound/");
			music.path = ft_strcat(music.path, music.read->d_name);
			music.file = dump_file(music.path, 0, &music.size);
			write_struct(music.file, fd, music.size);
			ft_strdel(&music.path);
		}
	}
	closedir(music.drt);
}
