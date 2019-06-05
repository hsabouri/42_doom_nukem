/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_deco.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:50:11 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/27 11:04:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static int					self_update(t_component *self, void *parent)
{
	t_display_deco_state *deco;

	(void)parent;
	deco = (t_display_deco_state *)self->state;
	if (self->display != 1 && ((!deco->invert
		&& deco->display_value == *deco->to_look_at) || (deco->invert
		&& deco->display_value != *deco->to_look_at)))
	{
		self->display = 1;
		return (1);
	}
	else if (self->display == 1 && !((!deco->invert
		&& deco->display_value == *deco->to_look_at) || (deco->invert
		&& deco->display_value != *deco->to_look_at)))
	{
		self->display = 0;
		return (1);
	}
	else if (self->display == 1)
		return (1);
	return (0);
}

static t_display_deco_state	*init_state(t_display_deco_state deco)
{
	t_display_deco_state *ret;

	ret = (t_display_deco_state *)safe_malloc(sizeof(t_display_deco_state),
		"components");
	*ret = deco;
	return (ret);
}

t_component					init_display_deco(t_display_deco_state deco,
t_component child)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size = (t_pix) {0, 0};
	ret.pos = (t_pix) {0, 0};
	ret.display = 0;
	ret.state = init_state(deco);
	ret.last_render = NULL;
	ret.update = &self_update;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.destroy = NULL;
	ret.childs = safe_anew(NULL, 1, sizeof(t_component), "components");
	apush(&ret.childs, &child);
	return (ret);
}
