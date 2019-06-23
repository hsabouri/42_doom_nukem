/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:06:59 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/04 13:07:02 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

#ifdef __linux__

t_game	init_audio(t_game game)
{
	return (game);
}

t_game	init_audio_tmp(t_game game)
{
	return (game);
}

t_array	stack_sounds(t_array chunks, size_t id, float vol)
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
