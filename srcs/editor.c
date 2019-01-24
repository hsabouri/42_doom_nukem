/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:29:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/23 15:21:02 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

inline t_editor		init_editor(void)
{
	return ((t_editor) {
		.zoom = 25.0,
		.offset = (t_vec2) {0.0, 0.0},
		.sel_point = -1,
		.components = NULL,
		.enabled = 1});
}

static t_vec2		move_point(t_event events, t_editor editor)
{
	t_vec2	new_point;

	new_point = (t_vec2) {events.x, events.y};
	new_point = vec2_sub(new_point, editor.offset);
	new_point = vec2_scale(new_point, 1 / editor.zoom);
	return (new_point);
}

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

	env.editor.sel_point = select_point(env.game, env.editor, env.events);
	if (env.editor.sel_point >= 0 && env.events.mouse[SDL_BUTTON_LEFT])
		env.game.points[env.editor.sel_point] = move_point(env.events, env.editor);
	env.editor.selecting = env.events.mouse[SDL_BUTTON_LEFT];
	draw_map(env.game, env.editor, env.current_buffer);
	legend_graphic(env.current_buffer);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	text("Editor3030", (t_pix) {10, 10}, env.sdl);
	legend_text(env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
