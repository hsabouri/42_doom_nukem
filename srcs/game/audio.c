/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:40:55 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/10 13:40:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

#ifndef __linux__

t_array	stack_sounds(t_array chunks, size_t id, float vol)
{
	t_chunk	sound;

	sound.chunk_id = id;
	sound.volume = vol;
	apush(&chunks, &sound);
	return (chunks);
}

void	play_music(t_game game, size_t id, size_t vol, size_t frame)
{
	t_music			*music;
	static size_t	play = -1;

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
		Mix_VolumeChunk(sound->sound, MIX_MAX_VOLUME * chunk->volume);
		Mix_PlayChannel(cpt, sound->sound, 0);
		cpt = (++cpt == 10) ? 0 : cpt;
	}
	return (game);
}

#endif
