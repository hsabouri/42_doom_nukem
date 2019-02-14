/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:08:23 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/11 11:08:25 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int		main_save(char *name)
{
	t_game		game;

	// game = generate_map(game);
	// save(name, game);
	game = load(name);
	return (0);
}
