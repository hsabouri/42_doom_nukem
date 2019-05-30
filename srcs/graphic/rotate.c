/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:19:13 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/30 16:25:50 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rotate_floor(size_t n, int mode, t_game game)
{
	if (mode == 1)
	{
		if (game.sectors[n].floor.y < 1)
		{
			game.sectors[n].floor.y += 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].floor.y -= 0.1;
		}
	}
	if (mode == 2)
	{
		if (game.sectors[n].floor.y > -1)
		{
			game.sectors[n].floor.y -= 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].floor.y += 0.1;
		}
	}
	rotate_floor2(n, mode, game);
}

void	rotate_floor2(size_t n, int mode, t_game game)
{
	if (mode == 3)
	{
		if (game.sectors[n].floor.x < 1)
		{
			game.sectors[n].floor.x += 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].floor.x -= 0.1;
		}
	}
	if (mode == 4)
	{
		if (game.sectors[n].floor.x > -1)
		{
			game.sectors[n].floor.x -= 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].floor.x += 0.1;
		}
	}
}

void	rotate_ceiling(size_t n, int mode, t_game game)
{
	if (mode == 1)
	{
		if (game.sectors[n].ceiling.y < 1)
		{
			game.sectors[n].ceiling.y += 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].ceiling.y -= 0.1;
		}
	}
	if (mode == 2)
	{
		if (game.sectors[n].ceiling.y > -1)
		{
			game.sectors[n].ceiling.y -= 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].ceiling.y += 0.1;
		}
	}
	rotate_ceiling2(n, mode, game);
}

void	rotate_ceiling2(size_t n, int mode, t_game game)
{
	if (mode == 3)
	{
		if (game.sectors[n].ceiling.x < 1)
		{
			game.sectors[n].ceiling.x += 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].ceiling.x -= 0.1;
		}
	}
	if (mode == 4)
	{
		if (game.sectors[n].ceiling.x > -1)
		{
			game.sectors[n].ceiling.x -= 0.1;
			if (check_z_limits(n, game) == 0)
				game.sectors[n].ceiling.x += 0.1;
		}
	}
}
