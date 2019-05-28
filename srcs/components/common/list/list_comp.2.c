/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_comp.2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:09:36 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 12:14:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list_comp.h"

static int		self_add(void *self_state)
{
	t_list_state		*state;
	int					ret;

	state = (t_list_state *)self_state;
	ret = state->add(state->parent);
	state->need_update = ret;
	return (ret);
}

t_array			list_init_childs(t_list_comp list, t_sdl *sdl)
{
	t_array		childs;
	t_component	current;

	childs = safe_anew(NULL, 2, sizeof(t_component), "component");
	current = init_cb_button((t_cb_button) {
		.pos = (t_pix) {list.pos.x + list.size.x - 40, list.pos.y},
		.size = (t_pix) {40, 40},
		.background = list.bg,
		.events = list.events,
		.callback = &self_add,
		.img = parse_tga("./textures/ui/plus.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN,
	}, sdl);
	apush(&childs, &current);
	return (childs);
}

t_array			clean_old(t_component *self, t_list_state *state, t_array built)
{
	t_array			ret;
	const size_t	new_size = built.len + ((state->add) ? 1 : 0);

	ret = safe_anew(NULL, new_size, sizeof(t_component), "components");
	if (state->add)
		apush(&ret, ashift(&self->childs));
	if (self->childs.len)
		clean_childs(self->childs);
	return (ret);
}

t_array			build_childs(t_component *self, t_list_state *state,
void *parent, t_sdl *sdl)
{
	t_array			built;
	t_list_content	*current;
	t_list_button	button;
	t_component		current_comp;
	size_t			i;

	built = state->build(parent);
	self->childs = clean_old(self, state, built);
	i = (size_t)-1;
	while ((current = (t_list_content *)apop(&built)) && i++ <= (size_t)-1)
	{
		button = (t_list_button) {.i = i, .parent = parent,
			.pos = (t_pix) {self->pos.x + 1, self->pos.y + 41 + 31 * i},
			.size = (t_pix) {self->size.x - 2, 30}, .img = current->img,
			.y_scroll = &state->y_scroll,
			.destroy_image = state->destroy_image};
		strncpy(button.text, current->text, 28);
		current_comp = init_list_button(button, *state, sdl);
		render_all(current_comp, sdl);
		apush(&self->childs, &current_comp);
	}
	if (built.mem)
		free(built.mem);
	return (self->childs);
}
