/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_legend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:24:33 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/10 13:43:43 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

void	legend(t_color *buf, t_sdl *sdl)
{
	int		y_pos;
	t_text	r_text;

	y_pos = HEIGHT - 30;
	r_text = text("Spawn: ", (t_pix) {20, y_pos}, sdl);
	draw_point((t_fvec2) {f_from_int(r_text.w + 10),
		f_from_int(HEIGHT - 25)}, 8, buf, MUSTARD);
	y_pos = y_pos - 30 - 5;
	r_text = text("Player: ", (t_pix) {20, y_pos}, sdl);
	draw_point((t_fvec2) {f_from_int(r_text.w + 10),
		f_from_int(HEIGHT - 60)}, 8, buf, MOONSTONE);
	y_pos = y_pos - 30 - 5;
	r_text = text("Point: ", (t_pix) {20, y_pos}, sdl);
	draw_point((t_fvec2) {f_from_int(r_text.w + 10),
		f_from_int(HEIGHT - 95)}, 8, buf, UBE);
}
