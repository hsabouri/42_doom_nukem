/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:29:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/31 14:23:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

inline t_editor		init_editor(void)
{
	t_editor res;
	res = (t_editor) {
		.zoom = 25.0,
		.offset = (t_vec2) {0.0, 0.0},
		.sel_point = -1,
		.components = NULL,
		.enabled = 1 };
	res.points_wall[0] = -1;
	res.points_wall[1] = -1;
	return (res);
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

	env.editor.sel_wall = -1;
	if (env.editor.tool == POINT)
	{
		env.editor.points_wall[0] = -1;
		env.editor.points_wall[1] = -1;
		env.editor.sel_point = select_point(env.game, env.editor, env.events);
		if (env.editor.sel_point >= 0 && env.events.mouse[SDL_BUTTON_LEFT])
			env.game.points[env.editor.sel_point] = point_from_mouse(env.events, env.editor);
		else if (env.editor.sel_point >= 0 && env.events.mouse_click[SDL_BUTTON_RIGHT])
			env.game = delete_point(env.editor.sel_point, env.game);
		else if (env.editor.sel_point == -1 && env.events.mouse_click[SDL_BUTTON_RIGHT])
			env.game = create_point(point_from_mouse(env.events, env.editor), env.game);
		env.editor.selecting = env.events.mouse[SDL_BUTTON_LEFT];
	}
	else if (env.editor.tool == WALL)
	{
		env.editor.sel_point = select_point(env.game, env.editor, env.events);
		env.editor.sel_wall = select_wall(env.game, env.editor, env.events);
		env.editor = select_multi_points(env.editor, env.events, env.editor.sel_point);
		if ((size_t)env.editor.points_wall[0] >= env.game.npoints)
			env.editor.points_wall[0] = -1;
		if ((size_t)env.editor.points_wall[1] >= env.game.npoints)
			env.editor.points_wall[1] = -1;
		if (env.editor.points_wall[0] >= 0 && env.editor.points_wall[1] >= 0)
		{
			env.game = create_wall(env.editor.points_wall, 0, env.game);
			env.editor.points_wall[0] = -1;
		}
		if (env.editor.sel_wall >= 0 && env.events.mouse_click[SDL_BUTTON_RIGHT])
			env.game = delete_wall((size_t)env.editor.sel_wall, env.game);
	}
	else if (env.editor.tool == PORTAL)
	{
		env.editor.points_wall[0] = -1;
		env.editor.points_wall[1] = -1;
		env.editor.sel_wall = select_wall(env.game, env.editor, env.events);
		if (env.editor.sel_wall >= 0 && env.events.mouse_click[SDL_BUTTON_RIGHT])
		{
			env.game = create_portal(env.editor.sel_wall, -1, env.game);
			env.editor.sel_wall = -1;
		}
	}

	draw_map(env.game, env.editor, env.current_buffer);
	legend_graphic(env.current_buffer);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	//text("Editor3030", (t_pix) {10, 10}, env.sdl);
	//legend_text(env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
