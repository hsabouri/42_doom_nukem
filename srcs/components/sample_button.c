/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:48:06 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/21 16:47:20 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>
#include "./sample_button.h"

void	button_render(const t_component self, t_color *buf)
{
	const int	state = *(const int *)self.state;

	background(buf, ((state % 2) ? RED : BLUE), self.size);
	//component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

int			button_update(t_component *self, void *elem)
{
	t_env		env;
	int			*state;

	env = *(t_env *)elem;
	state = (int *)self->state;
	if (is_clicked_on(*self, env.events))
	{
		(*state)++;
		return (1);
	}
	else
		return (0);
}

t_component	init_button(char *str, t_sdl *sdl)
{
	t_component component;
	
	component.img.content = NULL;
	component.text = component_text(str, component.pos, sdl);
	component.size.x = component.text.w + 10;
	component.size.y = component.text.h + 10;
	component.pos.x = WIDTH - 20 - component.size.x;
	component.pos.y = HEIGHT - 20 - component.size.y;
	component.text.x = component.size.x / 2 - component.text.w / 2 + 1;
	component.text.y = component.size.y / 2 - component.text.h / 2 + 2;
	component.display = 1;
	component.state = (void *)malloc(sizeof(int));
	*((int *)component.state) = 0;
	component.update = &button_update;
	component.render = &button_render;
	component.destroy = NULL;
	component.childs = anew(NULL, 0, sizeof(t_component));
	component.last_render = NULL;
	return (component);
}

