/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_textures_musics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:25:46 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/01 16:23:32 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

size_t				write_textures(int fd, t_img *textures, size_t ntextures,\
int index)
{
	t_c_img	ftextures;
	size_t	i;
	size_t	loc_content;

	i = 0;
	loc_content = 0;
	while (i < ntextures)
	{
		ftextures.magic = TEXT_MAGIC + i;
		ftextures.width = textures[i].width;
		ftextures.height = textures[i].height;
		if (i == 0)
			loc_content = (size_t)index;
		else
			loc_content += (size_t)(textures[i - 1].width *
				textures[i - 1].height) * sizeof(t_color);
		ftextures.content = loc_content;
		printf("loc_content = %zu\n", loc_content);
		write_struct(&ftextures, fd, sizeof(t_c_img));
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
