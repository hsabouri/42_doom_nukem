/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:29:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/01 14:22:40 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_env				editor_loop(t_env env)
{
	t_color			*content;
	int				pitch;
	
	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	env.current_buffer = content;

	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);

	*env.component = trigger_component(&env, *env.component, &env.sdl);
	display_component(*env.component, &env.sdl);

	display_text(env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
