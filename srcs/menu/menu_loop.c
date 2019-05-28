/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 13:02:57 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/30 13:03:04 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

void	menu_loop(t_env *env)
{
	*env->component = trigger_component(env, *env->component, &env->sdl);
	display_component(*env->component, &env->sdl);
	SDL_RenderPresent(env->sdl.renderer);
}
