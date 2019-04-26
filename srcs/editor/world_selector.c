/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_world_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:16:54 by hugo              #+#    #+#             */
/*   Updated: 2019/03/16 15:39:53 by lbougero         ###   ########.fr       */
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
