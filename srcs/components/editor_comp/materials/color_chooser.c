/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_chooser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/19 14:13:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static void		self_render(const t_component self, t_color *buf)
{
	background(buf, GREY, self.size);
	component_image(self.img, (t_pix) {1, 1}, self.size, buf);
}

static int		self_update(t_component *self, void *parent)
{
	const t_event	events = ((t_editor_mat_state *)parent)->env->events;
	t_color			color;
	t_pix			pos;

	if (is_clicked_on(*self, events))
	{
		pos = (t_pix) {events.x - self->pos.x, events.y - self->pos.y};
		color = self->img.content[pos.x + pos.y * self->img.width];
		if (self->state && *(t_color **)self->state)
			**(t_color **)self->state = color;
		return (1);
	}
	return (0);
}

t_component		init_color_chooser(t_color **to_change,
t_pix pos, t_sdl *sdl)
{
	t_component			ret;

	ret = default_component(NULL, (t_pix) {302, 322}, sdl);
	ret.img = parse_tga("./textures/ui/mire.tga");
	ret.state = to_change;
	ret.pos = pos;
	ret.display = 1;
	ret.update = &self_update;
	ret.destroy = &no_destroy;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	return (ret);
}

