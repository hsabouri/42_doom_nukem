/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_entity_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/22 12:15:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ev_ac.h"
#include "../../common/common.h"
#include "../../../common/entity_type_to_text.h"

static t_array		generator_loop(t_game game, t_editor_ev_ac_state *state,
t_list_content curr, t_array ret)
{
	size_t	i;

	i = 0;
	while (i < game.nentities)
	{
		if (state->selected_entity == (ssize_t)(game.nentities - i))
			ft_strncpy(curr.text, "unavailable", 28);
		else
			type_to_text(game.entities[game.nentities - i - 1].type, curr.text);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static t_array		generator(void *parent)
{
	t_editor_ev_ac_state	*state;
	t_game					game;
	t_list_content			curr;
	t_array					ret;
	size_t					i;

	state = ((t_editor_ev_ac_state *)(
		((t_display_deco_state *)parent)->state));
	game = state->env->game;
	state->selected_entity_2 = -1;
	ret = safe_anew(NULL, game.nentities + 1,
		sizeof(t_list_content), "component test");
	i = 0;
	curr.img.content = NULL;
	ret = generator_loop(game, state, curr, ret);
	if (state->selected_entity == (ssize_t)(game.nentities - i))
		ft_strncpy(curr.text, "unavailable", 28);
	else
		ft_strncpy(curr.text, "player", 28);
	apush(&ret, &curr);
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_ev_ac_state	*state;

	state = ((t_editor_ev_ac_state *)(
		((t_display_deco_state *)parent)->state));
	state->selected_entity_2 = i;
	return (0);
}

t_component			create_list_seconds_entity(t_env *env, int *external,
t_sdl *sdl)
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
		(t_pix) {666, 2},
		(t_pix) {200, HEIGHT},
		0,
		external
	}, sdl);
	return (ret);
}
