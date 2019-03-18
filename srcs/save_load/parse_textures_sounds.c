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

#include <doom.h>

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

static void	parse_music(t_save_music music, void *buf, t_save save,\
size_t i)
{
	t_c_music	struc_m;
	int			fd;

	struc_m = *(t_c_music *)dump_struct(buf, save.index + i *
		sizeof(t_c_music), sizeof(t_c_music), save.max);
	if (music.type == MUSIC)
		verify_magic(&struc_m, MUSIC_MAGIC, i);
	else
		verify_magic(&struc_m, SOUND_MAGIC, i);
	music.path = (char *)malloc(sizeof(char) * (32 + ft_strlen(ft_itoa(i))));
	music.path = (music.type == MUSIC) ? ft_strcpy(music.path,
		"./audio_tmp/music_tmp/music_") : ft_strcpy(music.path,
		"./audio_tmp/sound_tmp/sound_");
	music.path = ft_strcat(music.path, ft_itoa(i));
	music.path = ft_strcat(music.path, ".ogg");
	fd = open(music.path, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	write(fd, buf + struc_m.content, struc_m.length);
	close(fd);
	ft_strdel(&music.path);
}

void		parse_audio(void *buf, t_save save, size_t n_entities, t_audio type)
{
	t_save_music	music;
	size_t			i;

	if (stat("./audio_tmp", &music.st) == -1)
		mkdir("./audio_tmp", 0700);
	if (stat("./audio_tmp/music_tmp", &music.st) == -1 && type == MUSIC)
		mkdir("./audio_tmp/music_tmp", 0700);
	else if (stat("./audio_tmp/sound_tmp", &music.st) == -1 && type == SOUND)
		mkdir("./audio_tmp/sound_tmp", 0700);
	i = 0;
	music.type = type;
	while (i < n_entities)
	{
		parse_music(music, buf, save, i);
		i++;
	}
}
