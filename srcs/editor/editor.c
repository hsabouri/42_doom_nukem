/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:29:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 15:51:00 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_env				editor_loop(t_env env, size_t frame)
{
	t_color			*content;
	int				pitch;

	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	env.current_buffer = content;
	background(content, RICH_BLACK, (t_pix) {WIDTH, HEIGHT});
	//env.editor = zoom_move(env.events, env.editor);

	env.editor.sel_wall = -1;
	env = env.editor.tools[env.editor.current_tool](env);

	legend(env.current_buffer, &env.sdl);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);

	*env.component = trigger_component(&env, *env.component, &env.sdl);
	display_component(*env.component, &env.sdl);

	display_text(&env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
