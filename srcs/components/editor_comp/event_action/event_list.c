/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/14 15:40:01 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ev_ac.h"
#include "../../common/common.h"

static t_array		generator(void *parent)
{
	const t_game	game = ((t_editor_ev_ac_state *)parent)->env->game;
	t_list_content	curr;
	t_array			ret;
	size_t			i;

	ret = safe_anew(NULL, game.waiting_events.len,
		sizeof(t_list_content), "component test");
	i = 0;
	while (i < game.waiting_events.len)
	{
		curr.img.content = NULL;
		ft_strncpy(curr.text, ft_itoa(game.waiting_events.len - i - 1), 28);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_ev_ac_state *state;

	state = (t_editor_ev_ac_state *)parent;
	state->selected = i;
	state->selected_entity = -1;
	state->selected_entity_2 = -1;
	state->selected_trigger = -1;
	state->refresh_second_entity = 1;
	return (0);
}

static int			on_add(void *parent)
{
	(void)parent;
	return (1);
}

static int			on_del(void *parent, size_t i)
{
	(void)parent;
	(void)i;
	return (1);
}

t_component			create_list_events(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		&on_del,
		&on_add,
		&on_click,
		"EVENTS",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {2, 2},
		(t_pix) {200, HEIGHT},
		0,
		NULL
	}, sdl);
	return (ret);
}
