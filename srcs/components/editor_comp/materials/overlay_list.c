/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:21:19 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/12 12:00:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static t_array		generator_loop(t_game game, t_list_content curr,
t_array ret, t_editor_mat_state *state)
{
	size_t	i;

	i = 0;
	while (i < game.nmaterials)
	{
		curr.img.content = NULL;
		if (!game.materials[game.nmaterials - i - 1].overlay
			&& game.nmaterials - i - 1 != state->selected)
		{
			curr.text[0] = 0;
			if (game.materials[game.nmaterials - i - 1].texture)
				curr.img = *game.materials[game.nmaterials - i - 1].texture;
			else
				ft_strncpy(curr.text, ft_itoa(game.nmaterials - i - 1), 28);
		}
		else
			ft_strncpy(curr.text, "unavailable", 28);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static t_array		generator(void *parent)
{
	t_editor_mat_state	*state;
	t_game				game;
	t_list_content		curr;
	t_array				ret;

	state = ((t_editor_mat_state *)(((t_display_deco_state *)parent)->state));
	game = state->env->game;
	curr.img.content = NULL;
	ret = safe_anew(NULL, 0, sizeof(t_list_content), "component");
	ret = generator_loop(game, curr, ret, state);
	curr.img.content = NULL;
	ft_strncpy(curr.text, "no overlay", 28);
	apush(&ret, &curr);
	return (ret);
}

int					enable_change_overlay(void *parent)
{
	t_editor_mat_state	*state;

	state = (t_editor_mat_state *)parent;
	state->display_overlay = 1;
	state->update_overlay = 1;
	return (1);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_mat_state	*state;
	t_game				*game;
	t_mat				*current;
	size_t				s;

	state = (t_editor_mat_state *)(((t_display_deco_state *)parent)->state);
	game = &state->env->game;
	current = &game->materials[state->selected];
	if (i == 0)
		current->overlay = NULL;
	else
	{
		current->overlay = &state->env->game.materials[i - 1];
		s = 0;
		while (s < game->nmaterials)
		{
			if (game->materials[s].overlay == current)
				game->materials[s].overlay = NULL;
			s++;
		}
	}
	state->display_overlay = 0;
	state->update_overlay = 0;
	return (0);
}

t_component			create_list_overlay(t_env *env, int *update_list,
t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		NULL,
		NULL,
		&on_click,
		"OVERLAY",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {WIDTH / 2 - 100, 12},
		(t_pix) {200, HEIGHT},
		0,
		update_list
	}, sdl);
	return (ret);
}
