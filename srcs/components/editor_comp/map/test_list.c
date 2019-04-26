/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:17:59 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/03 16:25:37 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"
#include "../../common/common.h"

//a supprimer a la fin

static t_array		generator(void *parent)
{
	const size_t	nbuttons = ((t_editor_map_state *)parent)->n_buttons;
	t_list_content	curr;
	t_array			ret;
	size_t			i;

	ret = safe_anew(NULL, nbuttons, sizeof(t_list_content), "component test");
	i = 0;
	while (i < nbuttons)
	{
		curr.img.content = NULL;
		ft_strncpy(curr.text, "Sector", 28);
		apush(&ret, &curr);
		++i;
	}
	return (ret);
}

static int			on_del(void *parent, size_t i)
{
	size_t	*nbuttons = &((t_editor_map_state *)parent)->n_buttons;

	(*nbuttons)--;
	return (1);
}

static int			on_add(void *parent)
{
	size_t	*nbuttons = &((t_editor_map_state *)parent)->n_buttons;

	(*nbuttons)++;
	return (1);
}

static int			on_click(void *parent, size_t i)
{
	printf("%zu\n", i);
	return (0);
}

t_component			create_list_sectors(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret = init_list_comp((t_list_comp) {
		&generator,
		&on_del,
		&on_add,
		&on_click,
		"Ma super liste",
		&env->events,
		(t_color) {70, 70, 70, 255},
		(t_pix) {2, 44},
		(t_pix) {200, 200}
	}, sdl);
	return (ret);
}
