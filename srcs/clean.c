/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:16:55 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/26 16:34:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

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

void		clean_texture(t_env env)
{
	SDL_DestroyTexture(env.sdl.buf);
}

void		clean_game(t_game game)
{
	size_t	cpt;

	free(game.entities);
	free(game.classes);
	free(game.sectors);
	free(game.walls);
	free(game.portals);
	free(game.points);
	free(game.materials);
	cpt = 0;
	while (cpt < game.ntextures)
	{
		free(game.textures[cpt].content);
		cpt++;
	}
	free(game.textures);
	cpt = 0;
	while (cpt < game.nmulti_mats)
	{
		free(game.multi_mats[cpt].mem);
		cpt++;
	}
	free(game.multi_mats);
	clean_music(game);
	free(game.chunks.mem);
	free(game.id_buf);
}