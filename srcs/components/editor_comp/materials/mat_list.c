/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:21:19 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/08 15:06:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static t_array		generator(void *parent)
{
	const size_t	nmats = ((t_editor_mat_state *)parent)->env->game.nmaterials;
	const t_mat		*mats = ((t_editor_mat_state *)parent)->env->game.materials;
	t_list_content	curr;
	t_array			ret;
	size_t			i;

	ret = safe_anew(NULL, nmats, sizeof(t_list_content), "component test");
	i = 0;
	while (i < nmats)
	{
		curr.img.content = NULL;
		ft_strncpy(curr.text, ft_itoa(nmats - i - 1), 28);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	t_editor_mat_state *state;

	state = (t_editor_mat_state *)parent;
	state->selected = i;
	state->selected_color = &state->env->game.materials[i].color;
	state->selected_filter = &state->env->game.materials[i].filter;
	state->selected_mode = &state->env->game.materials[i].mode;
	return (0);
}

static int			on_add(void *parent)
{
	const t_editor_mat_state	*state = (t_editor_mat_state *)parent; 
	t_env						*env;
	
	env = ((t_editor_mat_state *)parent)->env;
	env->game = create_material(state->selected, env->game);
	on_click(parent, env->game.nmaterials - 1);
	return (1);
}

static int			on_del(void *parent, size_t i)
{
	t_env	*env;
	
	env = ((t_editor_mat_state *)parent)->env;
	if (env->game.nmaterials <= 1)
		return (0);
	on_click(parent, 0);
	env->game = delete_material(i, env->game);
	return (1);
}

t_component			create_list_materials(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		&on_del,
		&on_add,
		&on_click,
		"MATERIALS",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {2, 2},
		(t_pix) {200, HEIGHT}
	}, sdl);
	return (ret);
}
