/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:54:02 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/15 15:30:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_sector(size_t start, size_t nwalls, t_game game)
{
	if ((game.sectors = (t_sector *)realloc(game.sectors, (game.nsectors + 1) *
		sizeof(t_sector))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	game.sectors[game.nsectors] = (t_sector) {
		start,
		nwalls,
		game.nsectors,
		-2,
		2,
		WHITE,
		game.materials,
		game.materials,
		fvec2_new(0, 0)
	};
	game.nsectors++;
	return (game);
}
