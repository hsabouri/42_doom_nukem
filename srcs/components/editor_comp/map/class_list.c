/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 18:25:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"
#include "../../common/common.h"
#include "../../../common/entity_type_to_text.h"

static t_array		generator(void *parent)
{
	t_list_content		curr;
	t_array				ret;
	size_t				i;
	t_editor_map_state	*state;
	t_game				game;

	state = ((t_editor_map_state *)(((t_display_deco_state *)parent)->state));
	game = state->env->game;
	ret = safe_anew(NULL, game.nclasses,
		sizeof(t_list_content), "component test");
	i = 0;
	curr.img.content = NULL;
	while (i < game.nclasses)
	{
		type_to_text(game.classes[game.nclasses - i - 1].type, curr.text);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_map_state	*state;

	state = ((t_editor_map_state *)(((t_display_deco_state *)parent)->state));
	state->selected_class = i;
	return (0);
}

t_component			create_list_class(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator, NULL, NULL, &on_click, "CLASS", &env->events,
		(t_color) {70, 70, 70, 255}, (t_pix) {WIDTH - 202, 44},
		(t_pix) {200, HEIGHT}, 0, NULL}, sdl);
	return (ret);
}
