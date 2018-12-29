/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:57:34 by iporsenn          #+#    #+#             */
/*   Updated: 2018/12/21 17:57:35 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	physic(t_game game, t_event events)
{
	t_game new_game;

	new_game = game;
	new_game.player = player_physic(game.player, events);
	return (new_game);
}
