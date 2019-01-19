/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:58:11 by hugo              #+#    #+#             */
/*   Updated: 2019/01/19 18:32:43 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

t_color				get_material_pixel(t_mat mat, t_proj proj, int y)
{
	int			t_y;
	int			t_x;
	t_img		tex;
	t_color		res;

	if (!mat.texture)
		return (mat.color);
	tex = *mat.texture;
	t_y = f_to_int(((proj.bot - y - 1) * proj.y_iter * tex.height) /\
		Y_ITER_MUL);
	t_x = f_to_int(proj.x_col * tex.width);
	if ((u_int32_t)t_y > tex.height || (u_int32_t)t_x > tex.width)
		return (mat.color);
	res = tex.content[t_x + t_y * tex.width];
	return (res);
}
