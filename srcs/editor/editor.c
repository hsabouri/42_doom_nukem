/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:29:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/13 12:17:41 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static t_editor		zoom_move(t_event events, t_editor editor)
{
	editor.offset.u -= events.keys[SDL_SCANCODE_D] * MOVE_SPEED;
	editor.offset.u += events.keys[SDL_SCANCODE_A] * MOVE_SPEED;
	editor.offset.v -= events.keys[SDL_SCANCODE_S] * MOVE_SPEED;
	editor.offset.v += events.keys[SDL_SCANCODE_W] * MOVE_SPEED;
	editor.zoom *= 1 + ZOOM_SPEED * events.wheel;
	if (editor.zoom <= 0.1)
		editor.zoom = 0.1;
	return (editor);
}

t_env				editor_loop(t_env env, size_t frame)
{
	t_color			*content;
	int				pitch;

	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	env.current_buffer = content;
	background(content, RICH_BLACK);
	env.editor = zoom_move(env.events, env.editor);

	env.editor.sel_wall = -1;
	env = env.editor.tools[env.editor.current_tool](env);

	draw_map(env.game, env.editor, env.current_buffer);
	legend(env.current_buffer, &env.sdl);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	text("Editor3030", (t_pix) {10, 10}, &env.sdl);
	display_text(&env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
