/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:21:19 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/09 11:28:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static t_array		generator(void *parent)
{
	const size_t	ntex = ((t_editor_mat_state *)parent)->env->game.ntextures;
	const t_mat		*tex = ((t_editor_mat_state *)parent)->env->game.textures;
	t_list_content	curr;
	t_array			ret;
	size_t			i;

	ret = safe_anew(NULL, ntex, sizeof(t_list_content), "component test");
	i = 0;
	while (i < ntex)
	{
		curr.img.content = NULL;
		ft_strncpy(curr.text, ft_itoa(ntex - i - 1), 28);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static int			on_click(void *parent, size_t i)
{
	printf("Ouesh %zu\n", i);
	return (0);
}

t_component			create_list_textures(t_env *env, t_pix pos, t_pix size, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		NULL,
		NULL,
		&on_click,
		"TEXTURES",
		&env->events,
		(t_color) {70, 70, 70, 255},
		pos,
		size
	}, sdl);
	return (ret);
}
