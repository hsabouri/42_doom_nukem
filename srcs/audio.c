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
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
		== -1)
	{
		console_error("doom_nukem", "Could not initialize SDL_Mixer.");
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(10);

	game.music = (t_music *)malloc(2 * sizeof(t_music));
	game.music[0].music = Mix_LoadMUS("./audio/test.ogg");
	game.music[1].music = Mix_LoadMUS("./audio/test2.ogg");

	game.sounds = (t_sound *)malloc(2 * sizeof(t_sound));
	game.sounds[0].sound = Mix_LoadWAV("audio/open_door.ogg");
	game.sounds[1].sound = Mix_LoadWAV("audio/dog.ogg");
	game.nmusics = 2;
	game.nsounds = 2;
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
	if (frame == 1)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
		Mix_PlayMusic(game.music[id].music, -1);
		play = id;
	}
	if (play != id)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
		Mix_PlayMusic(game.music[id].music, -1);
		play = id;
	}
}

t_game	play_sounds(t_game game)
{
	t_chunk		*chunk;
	static int	cpt = 0;

	while ((chunk = (t_chunk *)apop(&game.chunks)))
	{
		Mix_VolumeChunk(game.sounds[chunk->chunk_id].sound, MIX_MAX_VOLUME *	
			chunk->volume);
		Mix_PlayChannel(cpt, game.sounds[chunk->chunk_id].sound, 0);
		cpt = (++cpt == 10) ? 0 : cpt;
	}
	return (game);
}

#else

t_game	init_audio(t_game game)
{
	game.nsounds = 0;
	game.nmusic = 0;
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