/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:06:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/09 16:55:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static t_mat	*select_mat(t_mat *mat, uint8_t depth)
{
	t_mat	*res;

	if (!mat)
		return (NULL);
	res = mat;
	while (res->overlay && depth)
	{
		res = res->overlay;
		depth -= 1;
	}
	return (res);
}

static t_fvec2	move(t_fvec2 values, t_event events, int mult_x, int mult_y)
{
	if (events.keys[SDL_SCANCODE_RSHIFT])
	{
		mult_x *= 5;
		mult_y *= 5;
	}
	if (events.keys[SDL_SCANCODE_UP])
		values.v += 100 * mult_y;
	if (events.keys[SDL_SCANCODE_DOWN])
		values.v -= 100 * mult_y;
	if (events.keys[SDL_SCANCODE_LEFT])
		values.u += 100 * mult_x;
	if (events.keys[SDL_SCANCODE_RIGHT])
		values.u -= 100 * mult_x;
	return (values);
}

t_env			scale_material_tool(t_env env, t_selected selected)
{
	t_mat	*p;

	p = NULL;
	if (selected.type == PART_WALL || (selected.type == PART_PORTAL
		&& (selected.mod == MOD_STEP || selected.mod == MOD_CEIL)))
		p = env.game.walls[selected.id].mat;
	else if (selected.type == PART_PORTAL && selected.mod == MOD_OPEN)
	{
		if (env.game.portals[env.game.walls[selected.id].portal].mat)
			p = env.game.portals[env.game.walls[selected.id].portal].mat;
	}
	else if (selected.type == PART_FLOOR)
		p = env.game.sectors[selected.id].floor_mat;
	else if (selected.type == PART_CEILING)
		p = env.game.sectors[selected.id].ceiling_mat;
	p = select_mat(p, env.editor.depth);
	if (p != NULL)
		p->sca = move(p->sca, env.events, 1, 1);
	return (env);
}

t_env			move_material_tool(t_env env, t_selected selected)
{
	t_mat	*p;

	p = NULL;
	if (selected.type == PART_WALL || (selected.type == PART_PORTAL
		&& (selected.mod == MOD_STEP || selected.mod == MOD_CEIL)))
		p = env.game.walls[selected.id].mat;
	else if (selected.type == PART_PORTAL && selected.mod == MOD_OPEN)
	{
		if (env.game.portals[env.game.walls[selected.id].portal].mat)
			p = env.game.portals[env.game.walls[selected.id].portal].mat;
	}
	else if (selected.type == PART_FLOOR)
		p = env.game.sectors[selected.id].floor_mat;
	else if (selected.type == PART_CEILING)
		p = env.game.sectors[selected.id].ceiling_mat;
	p = select_mat(p, env.editor.depth);
	if (p != NULL)
		p->pos = move(p->pos, env.events,
			-1 * ((p->mode == SKYBOX) ? 200 : 5),
			-1 * ((p->mode == SKYBOX) ? 200 : 100));
	return (env);
}

t_env			move_texture_tool(t_env env, t_selected selected)
{
	t_fvec2	*to_move;

	to_move = NULL;
	if (selected.type == PART_WALL || selected.type == PART_PORTAL)
		to_move = &env.game.walls[selected.id].tex_pos;
	else if (selected.type == PART_FLOOR || selected.type == PART_CEILING)
		to_move = &env.game.sectors[selected.id].tex_pos;
	if (to_move != NULL)
		*to_move = move(*to_move, env.events, 1, 1);
	return (env);
}
