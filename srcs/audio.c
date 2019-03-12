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
