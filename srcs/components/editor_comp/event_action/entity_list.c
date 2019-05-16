/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/15 13:42:50 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ev_ac.h"
#include "../../common/common.h"

static t_array		generator(void *parent)
{
	const t_editor_ev_ac_state	*state = ((t_editor_ev_ac_state *)(
		((t_display_deco_state *)parent)->state));
	const t_game	game = state->env->game;
	t_list_content	curr;
	t_array			ret;
	size_t			i;

	ret = safe_anew(NULL, game.nentities + 1,
		sizeof(t_list_content), "component test");
	i = 0;
	curr.img.content = NULL;
	while (i < game.nentities)
	{
		ft_strncpy(curr.text, game.entities[game.nentities - i - 1].type, 28);
		apush(&ret, &curr);
		++i;
	}
	ft_strncpy(curr.text, "player", 28);
	apush(&ret, &curr);
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_ev_ac_state	*state;
	
	state = ((t_editor_ev_ac_state *)(
		((t_display_deco_state *)parent)->state));
	state->selected_entity = i;
	state->selected_entity_2 = -1;
	state->selected_trigger = -1;
	state->refresh_second_entity = 1;
	return (0);
}

t_component			create_list_entity(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		NULL,
		NULL,
		&on_click,
		"ENTITY A",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {222, 2},
		(t_pix) {200, HEIGHT},
		0,
		NULL
	}, sdl);
	return (ret);
}