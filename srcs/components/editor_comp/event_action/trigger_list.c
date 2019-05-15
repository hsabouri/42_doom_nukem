/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/15 11:22:38 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ev_ac.h"
#include "../../common/common.h"

static t_array		generator(void *parent)
{
	t_list_content	curr;
	t_array			ret;

	(void)parent;
	ret = safe_anew(NULL, 5, sizeof(t_list_content), "component test");
	curr.img.content = NULL;
	ft_strncpy(curr.text, "sector* (0x4)", 28);
	apush(&ret, &curr);
	ft_strncpy(curr.text, "interact (0x3)", 28);
	apush(&ret, &curr);
	ft_strncpy(curr.text, "touch (0x2)", 28);
	apush(&ret, &curr);
	ft_strncpy(curr.text, "see (0x1)", 28);
	apush(&ret, &curr);
	ft_strncpy(curr.text, "n/a (0x0)", 28);
	apush(&ret, &curr);
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_ev_ac_state	*state;
	
	state = ((t_editor_ev_ac_state *)(
		((t_display_deco_state *)parent)->state));
	state->selected_trigger = i;
	state->selected_entity_2 = -1;
	printf("i: %zu\n", i);
	return (0);
}

t_component			create_list_trigger(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		NULL,
		NULL,
		&on_click,
		"TRIGGER",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {444, 2},
		(t_pix) {200, HEIGHT},
		0,
		NULL
	}, sdl);
	return (ret);
}