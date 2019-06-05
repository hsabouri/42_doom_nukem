/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:40:28 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/04 14:40:30 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

#ifndef __linux__

static t_array	init_music_loop(t_array a_music, DIR *drt)
{
	t_dirent	*read;
	char		*path;
	t_music		music;

	while ((read = readdir(drt)))
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..")
			&& read->d_type == 8
			&& (ft_strcmp(ft_strrchr(read->d_name, '.'), ".ogg") == 0))
		{
			path = (char *)safe_malloc((23 + ft_strlen(read->d_name)
				* sizeof(char)), "audio");
			path = ft_strcpy(path, "./audio_tmp/music_tmp/");
			path = ft_strcat(path, read->d_name);
			music.music = Mix_LoadMUS(path);
			apush(&a_music, &music);
			ft_strdel(&path);
		}
	}
	return (a_music);
}

static t_array	init_music(t_array a_music)
{
	DIR			*drt;

	if (!(drt = opendir("./audio_tmp/music_tmp")))
	{
		console_error("audio", "Could not open directory");
		exit(EXIT_FAILURE);
	}
	a_music = safe_anew(NULL, 1, sizeof(t_music), "audio");
	a_music = init_music_loop(a_music, drt);
	closedir(drt);
	return (a_music);
}

static t_array	init_sound_loop(t_array a_sound, DIR *drt)
{
	t_dirent	*read;
	char		*path;
	t_sound		sound;

	while ((read = readdir(drt)))
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..")
			&& read->d_type == 8
			&& (ft_strcmp(ft_strrchr(read->d_name, '.'), ".ogg") == 0))
		{
			path = (char *)safe_malloc((23 + ft_strlen(read->d_name)
				* sizeof(char)), "audio");
			path = ft_strcpy(path, "./audio_tmp/sound_tmp/");
			path = ft_strcat(path, read->d_name);
			sound.sound = Mix_LoadWAV(path);
			apush(&a_sound, &sound);
			ft_strdel(&path);
		}
	}
	return (a_sound);
}

static t_array	init_sound(t_array a_sound)
{
	DIR			*drt;

	if (!(drt = opendir("./audio_tmp/sound_tmp")))
	{
		console_error("audio", "Could not open directory");
		exit(EXIT_FAILURE);
	}
	a_sound = safe_anew(NULL, 1, sizeof(t_sound), "audio");
	a_sound = init_sound_loop(a_sound, drt);
	closedir(drt);
	return (a_sound);
}

t_game			init_audio_tmp(t_game game)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
		MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		console_error("doom_nukem", "Could not initialize SDL_Mixer.");
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(100);
	game.music = init_music(game.music);
	game.sounds = init_sound(game.sounds);
	game.played_music = 0;
	game.chunks = safe_anew(NULL, 10, sizeof(t_chunk), "audio");
	return (game);
}

#endif
