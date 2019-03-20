/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c  	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:48:52 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/28 14:48:53 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

#ifndef __linux__

t_game	init_audio(t_game game)
{
	DIR			*drt;
	t_dirent	*read;
	char		*path;
	t_music		music;
	t_sound		sound;
	size_t		i;

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
		== -1)
	{
		console_error("doom_nukem", "Could not initialize SDL_Mixer.");
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(10);

	i = 0;
	if (!(drt = opendir("./audio_tmp/music_tmp")))
	{
		console_error("Audio", "Could not open directory");
		exit(EXIT_FAILURE);
	}
	game.music = anew(NULL, 1, sizeof(t_music));
	while ((read = readdir(drt)))
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..")
			&& read->d_type == 8 && 
			(ft_strcmp(ft_strrchr(read->d_name, '.'), ".ogg") == 0))
		{
			path = (char *)malloc(sizeof(char) * (23 + ft_strlen(read->d_name)));
			path = ft_strcpy(path, "./audio_tmp/music_tmp/");
			path = ft_strcat(path, read->d_name);
			music.music = Mix_LoadMUS(path);
			apush(&game.music, &music);
			i++;
			ft_strdel(&path);
		}
	}
	closedir(drt);

	i = 0;
	if (!(drt = opendir("./audio_tmp/sound_tmp")))
	{
		console_error("Audio", "Could not open directory");
		exit(EXIT_FAILURE);
	}
	game.sounds = anew(NULL, 1, sizeof(t_sound));
	while ((read = readdir(drt)))
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..")
			&& read->d_type == 8 &&
			(ft_strcmp(ft_strrchr(read->d_name, '.'), ".ogg") == 0))
		{
			path = (char *)malloc(sizeof(char) * (23 + ft_strlen(read->d_name)));
			path = ft_strcpy(path, "./audio_tmp/sound_tmp/");
			path = ft_strcat(path, read->d_name);
			sound.sound = Mix_LoadWAV(path);
			apush(&game.sounds, &sound);
			i++;
			ft_strdel(&path);
		}
	}
	closedir(drt);
	
	game.played_music = 0;
	game.chunks = anew(NULL, 10, sizeof(t_chunk));
	return (game);
}

t_array	stack_sounds(t_array chunks, size_t id, u_int32_t vol)
{
	t_chunk	sound;

	sound.chunk_id = id;
	sound.volume = vol;
	apush(&chunks, &sound);
	return (chunks);
}

void	play_music(t_game game, size_t id, size_t vol, size_t frame)
{
	static size_t	play = -1;
	t_music			*music;
	if (frame == 1)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
		music = (t_music *)anth(&game.music, id);
		Mix_PlayMusic(music->music, -1);
		play = id;
	}
	if (play != id)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
		music = (t_music *)anth(&game.music, id);
		Mix_PlayMusic(music->music, -1);
		play = id;
	}
}

t_game	play_sounds(t_game game)
{
	t_chunk		*chunk;
	t_sound		*sound;
	static int	cpt = 0;

	while ((chunk = (t_chunk *)apop(&game.chunks)))
	{
		sound = (t_sound *)anth(&game.sounds, chunk->chunk_id);
		Mix_VolumeChunk(sound->sound, MIX_MAX_VOLUME *	chunk->volume);
		Mix_PlayChannel(cpt, sound->sound, 0);
		cpt = (++cpt == 10) ? 0 : cpt;
	}
	return (game);
}

#else

t_game	init_audio(t_game game)
{
	return (game);
}

t_array	stack_sounds(t_array chunks, size_t id, u_int32_t vol)
{
	(void)id;
	(void)vol;
	return (chunks);
}

void	play_music(t_game game, size_t id, size_t vol, size_t frame)
{
	(void)game;
	(void)id;
	(void)vol;
	(void)frame;
}

t_game	play_sounds(t_game game)
{
	return (game);
}

#endif