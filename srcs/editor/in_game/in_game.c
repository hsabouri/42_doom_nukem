/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:01:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/01 15:04:19 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

void		print_selected(t_selected selected, t_sdl *sdl)
{
	t_text	s;
	const char	*id = ft_itoa(selected.id);

	s = text("Type: ", (t_pix){10, 10}, sdl);
	if (selected.type == PART_FLOOR)
		s = text("Floor", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_CEILING)
		s = text("Roof", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_ENTITY)
		s = text("Entity", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_WALL)
		s = text("Wall", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_PORTAL)
		s = text("Portal", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else
		s = text("N/A", (t_pix){s.x + s.w + 10, 10}, sdl);
	s = text("Modifier: ", (t_pix){10, s.y + s.h + 5}, sdl);
	if (selected.mod == MOD_CEIL)
		s = text("Ceiling", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_STEP)
		s = text("Step", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_OPEN)
		s = text("Opening", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_NO)
		s = text("N/A", (t_pix){s.x + s.w + 10, s.y}, sdl);
	if (selected.type == PART_FLOOR || selected.type == PART_CEILING)
		s = text("Sector id: ", (t_pix){10, s.y + s.h + 5}, sdl);
	else
		s = text("Object id: ", (t_pix){10, s.y + s.h + 5}, sdl);
	s = text(id, (t_pix){s.x + s.w + 10, s.y}, sdl);
	free((char *)id);
}

t_game_tool	select_tool(t_env env)
{
	t_game_tool res;
	if (env.events.keys[SDL_SCANCODE_T])
		res = TEXTURE_MOVE;
	else if (env.events.keys[SDL_SCANCODE_Y])
		res = MATERIAL_MOVE;
	else if (env.events.keys[SDL_SCANCODE_U])
		res = MATERIAL_SCALE;
	else if (env.events.keys[SDL_SCANCODE_H])
		res = SECTOR_HEIGHT;
	else if (env.events.keys[SDL_SCANCODE_G])
		res = MATERIAL_CHANGE;
	else
		res = env.editor.game_tool;
	env.events.keys[SDL_SCANCODE_T] = 0;
	return (res);
}

t_env		game_editing(t_env env, t_player player)
{
	t_sector	*sector;
	t_game_tool	last;
	t_selected	sel;

	sector = &env.game.sectors[player.my_entity.physic.sector_id];
	sel = world_selector(env.game);
	last = env.editor.game_tool;
	print_selected(sel, &env.sdl);
	env.editor.game_tool = select_tool(env);
	if (last != env.editor.game_tool)
		env.editor.depth = 0;
	if (env.editor.game_tool != TOOL_NO)
		env = env.editor.game_tools[env.editor.game_tool](env, sel);
	return (env);
}