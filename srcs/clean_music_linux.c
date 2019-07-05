/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_music_linux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:16:55 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/05 10:11:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#ifndef __linux__

void		clean_music(t_game game)
{
	t_music	*music;
	t_sound	*sound;

	while ((music = (t_music *)apop(&game.music)))
		Mix_FreeMusic(music->music);
	free(game.music.mem);
	while ((sound = (t_sound *)apop(&game.sounds)))
		Mix_FreeChunk(sound->sound);
	free(game.sounds.mem);
	Mix_CloseAudio();
}

#else

void		clean_music(t_game game)
{
	(void)game;
}

#endif
