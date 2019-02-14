/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_legend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:24:33 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/08 15:20:06 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

/*void	legend_text(t_sdl sdl)
{
	int		y_pos;
	t_pix	size;

	y_pos = HEIGHT - 30;
	size = text("Spawn: ", (t_pix) {20, y_pos}, sdl);
	y_pos = y_pos - 30 - 5;
	size = text("Player: ", (t_pix) {20, y_pos}, sdl);
	y_pos = y_pos - 30 - 5;
	size = text("Point: ", (t_pix) {20, y_pos}, sdl);
}*/

void	legend_graphic(t_color *buf)
{
	draw_point((t_fvec2) {f_from_int(130), f_from_int(HEIGHT - 25)}, 8, buf, MUSTARD);
	draw_point((t_fvec2) {f_from_int(130), f_from_int(HEIGHT - 60)}, 8, buf, MOONSTONE);
	draw_point((t_fvec2) {f_from_int(130), f_from_int(HEIGHT - 95)}, 8, buf, UBE);
}
