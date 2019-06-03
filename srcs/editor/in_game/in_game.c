/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:01:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 14:29:08 by hsabouri         ###   ########.fr       */
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

t_game		tilt_floor_ceil(t_game game, t_event events)
{
	find_center_sectors(game);
	if (events.keys[SDL_SCANCODE_KP_6] || events.keys[SDL_SCANCODE_6])
		rotate_floor(game.player.my_entity.physic.sector_id, 1, game);
	if (events.keys[SDL_SCANCODE_KP_4] || events.keys[SDL_SCANCODE_4])
		rotate_floor(game.player.my_entity.physic.sector_id, 2, game);
	if (events.keys[SDL_SCANCODE_KP_8] || events.keys[SDL_SCANCODE_8])
		rotate_floor(game.player.my_entity.physic.sector_id, 3, game);
	if (events.keys[SDL_SCANCODE_KP_2] || events.keys[SDL_SCANCODE_2])
		rotate_floor(game.player.my_entity.physic.sector_id, 4, game);
	if (events.keys[SDL_SCANCODE_KP_7] || events.keys[SDL_SCANCODE_7])
		rotate_ceiling(game.player.my_entity.physic.sector_id, 1, game);
	if (events.keys[SDL_SCANCODE_KP_9] || events.keys[SDL_SCANCODE_9])
		rotate_ceiling(game.player.my_entity.physic.sector_id, 2, game);
	if (events.keys[SDL_SCANCODE_KP_1] || events.keys[SDL_SCANCODE_1])
		rotate_ceiling(game.player.my_entity.physic.sector_id, 3, game);
	if (events.keys[SDL_SCANCODE_KP_3] || events.keys[SDL_SCANCODE_3])
		rotate_ceiling(game.player.my_entity.physic.sector_id, 4, game);
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
	env.game = tilt_floor_ceil(env.game, env.events);
	if (env.events.keys[SDL_SCANCODE_KP_ENTER] && sel.type == PART_PORTAL)
	{
		portal = &env.game.portals[env.game.walls[sel.id].portal];
		env.events.keys[SDL_SCANCODE_KP_ENTER] = 0;
		portal->blocking = !portal->blocking;
	}
	return (env);
}
