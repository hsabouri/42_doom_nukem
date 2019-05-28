/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:24:15 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 11:38:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static int		self_update(t_component *self, void *parent)
{
	(void)self;
	(void)parent;
	return (0);
}

static void		self_render(const t_component self, t_color *buf)
{
	background(buf, *(t_color *)self.state, self.size);
}

t_component		init_simple_rectangle(t_pix pos, t_pix size,
t_color background, t_sdl *sdl)
{
	t_component ret;

	ret = default_component((t_color *)safe_malloc(sizeof(t_color),
		"component"),
		size, sdl);
	*(t_color *)ret.state = background;
	ret.pos = pos;
	ret.update = &self_update;
	ret.render = &self_render;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	return (ret);
}
