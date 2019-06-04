/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:44:55 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/15 15:18:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_point(t_vec2 pts, ssize_t index, t_game game)
{
	index = (index >= 0) ? index : game.npoints;
	if ((game.points = array_open(game.points,
		index, game.npoints, sizeof(t_vec2))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	game.points[index] = pts;
	++game.npoints;
	return (game);
}
