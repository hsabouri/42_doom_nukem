/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ingame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:01:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/17 14:52:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		print_selected(t_game game, t_selected selected, t_sdl *sdl)
{
	t_text	s;

	s = text("Type: ", (t_pix){10, 10}, sdl);
	if (selected.type == PART_FLOOR)
		text("Floor", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_CEILING)
		text("Roof", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_ENTITY)
		text("Entity", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_WALL)
		text("Wall", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.type == PART_PORTAL)
		text("Portal", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else
		text("N/A", (t_pix){s.x + s.w + 10, 10}, sdl);
	s = text("Modifier: ", (t_pix){10, s.y + s.h + 5}, sdl);
	if (selected.mod == MOD_CEIL)
		text("Ceiling", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_STEP)
		text("Step", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_OPEN)
		text("Opening", (t_pix){s.x + s.w + 10, s.y}, sdl);
	else if (selected.mod == MOD_NO)
		text("N/A", (t_pix){s.x + s.w + 10, s.y}, sdl);
	if (selected.type == PART_FLOOR || selected.type == PART_CEILING)
		s = text("Sector id: ", (t_pix){10, s.y + s.h + 5}, sdl);
	else
		s = text("Object id: ", (t_pix){10, s.y + s.h + 5}, sdl);
	text(ft_itoa(selected.id), (t_pix){s.x + s.w + 10, s.y}, sdl);
}

t_game		game_editing(t_game game, t_event events, t_player player,
t_sdl *sdl)
{
	t_sector	*sector;
	t_selected	sel;

	sector = &game.sectors[player.physic.sector_id];
	sel = world_selector(game);
	print_selected(game, sel, sdl);
	if (game.player.physic.look_v >= 0 && events.keys[SDL_SCANCODE_KP_PLUS])
		*sector = sector_height(game, *sector, PART_CEILING, 0.1);
	if (game.player.physic.look_v >= 0 && events.keys[SDL_SCANCODE_KP_MINUS])
		*sector = sector_height(game, *sector, PART_CEILING, -0.1);
	if (game.player.physic.look_v < 0 && events.keys[SDL_SCANCODE_KP_PLUS])
		*sector = sector_height(game, *sector, PART_FLOOR, 0.1);
	if (game.player.physic.look_v < 0 && events.keys[SDL_SCANCODE_KP_MINUS])
		*sector = sector_height(game, *sector, PART_FLOOR, -0.1);
	return (game);
}
