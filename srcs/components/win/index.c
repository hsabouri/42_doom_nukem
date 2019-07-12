/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 12:07:00 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:26:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../root.h"
#include "../common/common.h"

static void		self_render(const t_component self, t_color *buf)
{
	component_image(self.img, self.pos, (t_pix) {WIDTH, HEIGHT}, buf);
}

t_component		init_win(t_env *env, t_sdl *sdl)
{
	t_component			ret;

	ret = default_component(NULL, (t_pix) {WIDTH, HEIGHT}, sdl);
	ret.img = parse_tga("./textures/menu/menu_win.tga", 0);
	ret.state = NULL;
	ret.pos = (t_pix) {0, 0};
	ret.display = 1;
	ret.update = NULL;
	ret.destroy = &no_destroy;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	ret = init_display_deco((t_display_deco_state)
		{(int *)&env->game_mode, WIN, NULL, 0}, ret);
	return (ret);
}
