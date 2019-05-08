/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:48:06 by hugo              #+#    #+#             */
/*   Updated: 2019/05/07 17:02:41 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"


t_component		init_simple_text(const char *s, t_pix pos, t_sdl *sdl)
{
	t_component ret;

	ret = default_component(NULL, (t_pix) {0, 0}, sdl);
	ret.pos = pos;
	ret.text = component_text(s, (t_pix) {0, 0}, sdl);
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	return (ret);
}

