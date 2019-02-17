/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_world_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:16:54 by hugo              #+#    #+#             */
/*   Updated: 2019/02/17 11:25:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>
#include <graphic.h>

t_selected			world_selector(t_game game)
{
	const size_t		sc_center = (WIDTH >> 1) + (HEIGHT >> 1) * WIDTH;
	const u_int32_t		serial = game.id_buf[sc_center];
	const t_selected	res = translate_out(serial);

	return (res);
}
