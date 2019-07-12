/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:01:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 14:43:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game_tool	select_tool(t_env env)
{
	t_game_tool res;

	if (env.events.keys[SDL_SCANCODE_T])
		res = TEXTURE_MOVE;
	else if (env.events.keys[SDL_SCANCODE_Y])
		res = MATERIAL_MOVE;
	else if (env.events.keys[SDL_SCANCODE_U])
		res = MATERIAL_SCALE;
	else if (env.events.keys[SDL_SCANCODE_J])
		res = SECTOR_HEIGHT;
	else if (env.events.keys[SDL_SCANCODE_G])
		res = MATERIAL_CHANGE;
	else
		res = env.editor.game_tool;
	env.events.keys[SDL_SCANCODE_T] = 0;
	env.events.keys[SDL_SCANCODE_Y] = 0;
	env.events.keys[SDL_SCANCODE_U] = 0;
	env.events.keys[SDL_SCANCODE_J] = 0;
	env.events.keys[SDL_SCANCODE_G] = 0;
	return (res);
}

t_game		tilt_floor_ceil(t_game game, t_event events, t_selected sel)
{
	int rotate;

	rotate = 0;
	if (sel.id < 0 || (sel.type != PART_FLOOR && sel.type != PART_CEILING)
		|| sel.id == game.player.my_entity.physic.sector_id)
		return (game);
	find_center_sectors(game);
	if (events.keys[SDL_SCANCODE_KP_6] || events.keys[SDL_SCANCODE_6])
		rotate = 1;
	if (events.keys[SDL_SCANCODE_KP_4] || events.keys[SDL_SCANCODE_4])
		rotate = 2;
	if (events.keys[SDL_SCANCODE_KP_8] || events.keys[SDL_SCANCODE_8])
		rotate = 3;
	if (events.keys[SDL_SCANCODE_KP_2] || events.keys[SDL_SCANCODE_2])
		rotate = 4;
	if (sel.type == PART_CEILING && rotate)
		rotate_ceiling(sel.id, rotate, game);
	else if (rotate)
		rotate_floor(sel.id, rotate, game);
	return (game);
}

t_game		swap_height_pos(t_game game, t_selected selected, t_event *events)
{
	t_vec3	tmp;

	if (selected.type == PART_CEILING || selected.type == PART_FLOOR)
	{
		tmp = game.sectors[selected.id].ceiling_b;
		game.sectors[selected.id].ceiling_b = game.sectors[selected.id].ceiling;
		game.sectors[selected.id].ceiling = tmp;
		tmp = game.sectors[selected.id].floor_b;
		game.sectors[selected.id].floor_b = game.sectors[selected.id].floor;
		game.sectors[selected.id].floor = tmp;
		events->keys[SDL_SCANCODE_N] = 0;
	}
	return (game);
}

t_game		entity_in_game_edit(t_game game, t_event events,
t_selected selected, t_game_tool tool)
{
	static t_selected	last = (t_selected) {.type = PART_NO};
	t_entity			*current;

	if (events.keys[SDL_SCANCODE_CAPSLOCK])
		selected = last;
	else
		last = selected;
	if (tool == SECTOR_HEIGHT && selected.type == PART_ENTITY)
	{
		current = &game.entities[selected.id];
		if (events.keys[SDL_SCANCODE_B])
		{
			current->physic.fly = !current->physic.fly;
			current->spawn.fly = !current->spawn.fly;
		}
	}
	return (game);
}

t_env		game_editing(t_env env, t_player player)
{
	t_sector	*sector;
	t_game_tool	last;
	t_selected	sel;
	t_portal	*portal;

	sector = &env.game.sectors[player.my_entity.physic.sector_id];
	sel = world_selector(env.game);
	last = env.editor.game_tool;
	env.editor.game_tool = select_tool(env);
	if (last != env.editor.game_tool)
		env.editor.depth = 0;
	if (env.editor.game_tool != TOOL_NO)
		env = env.editor.game_tools[env.editor.game_tool](env, sel);
	if (env.events.keys[SDL_SCANCODE_N])
		env.game = swap_height_pos(env.game, sel, &env.events);
	env.game = tilt_floor_ceil(env.game, env.events, sel);
	env.game = entity_in_game_edit(env.game, env.events, sel,
		env.editor.game_tool);
	if (env.events.keys[SDL_SCANCODE_KP_ENTER] && sel.type == PART_PORTAL)
	{
		portal = &env.game.portals[env.game.walls[sel.id].portal];
		env.events.keys[SDL_SCANCODE_KP_ENTER] = 0;
		portal->blocking = !portal->blocking;
	}
	return (env);
}
