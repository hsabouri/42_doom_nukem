/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:44:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		dead_loop(t_env *env)
{
	SDL_UnlockTexture(env->sdl.buf);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.buf, NULL, NULL);
	trigger_component(env, *env->component, &env->sdl);
	display_component(*env->component, &env->sdl);
	SDL_RenderPresent(env->sdl.renderer);
}

void		win_loop(t_env *env)
{
	SDL_UnlockTexture(env->sdl.buf);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.buf, NULL, NULL);
	trigger_component(env, *env->component, &env->sdl);
	display_component(*env->component, &env->sdl);
	SDL_RenderPresent(env->sdl.renderer);
}
