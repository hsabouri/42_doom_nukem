/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 15:07:29 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 18:22:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include <graphic.h>

void			render_preview(t_mat mat, int width, int height, t_color *buf)
{
	t_tex_proj	tex;
	int			y;
	int			x;
	t_color		c;

	tex.mat = mat;
	tex.angle = 0;
	tex.ambient = WHITE;
	tex.x = 0;
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			tex.p = 0;
			c = get_mat_pixel(tex.mat, tex, fvec2_new(
				f_from_int(x) / width, f_from_int(y) / width), 0);
			buf[x + y * width] = (c.a > 0) ? c : GREEN;
			y++;
		}
		x++;
	}
}

static void		self_render(const t_component self, t_color *buf)
{
	const t_editor_mat_state	state = *(t_editor_mat_state *)self.state;

	render_preview(state.env->game.materials[state.selected],
		300, 300, buf);
}

t_component		init_preview(t_editor_mat_state *parent, t_pix pos, t_sdl *sdl)
{
	t_component			ret;

	ret = default_component(parent, (t_pix) {300, 300}, sdl);
	ret.state = parent;
	ret.pos = pos;
	ret.display = 1;
	ret.update = NULL;
	ret.destroy = &no_destroy;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	return (ret);
}
