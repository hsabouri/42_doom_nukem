/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:37:21 by hugo              #+#    #+#             */
/*   Updated: 2019/03/14 15:55:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_mat			*change(t_mat *mat, t_env *env)
{
	if (env->events.keys[SDL_SCANCODE_LEFT] && env->game.nmaterials >= 2)
	{
		if (mat >= &env->game.materials[1])
			mat = (t_mat *)((size_t)mat - sizeof(t_mat));
		else
			mat = &env->game.materials[env->game.nmaterials - 1];
		env->events.keys[SDL_SCANCODE_LEFT] = 0;
	}
	else if (env->events.keys[SDL_SCANCODE_RIGHT] && env->game.nmaterials >= 2)
	{
		if (mat < &env->game.materials[env->game.nmaterials - 1])
			mat = (t_mat *)((size_t)mat + sizeof(t_mat));
		else
			mat = &env->game.materials[0];
		env->events.keys[SDL_SCANCODE_RIGHT] = 0;
	}
	return (mat);
}

static t_portal	link_unlink_opening(t_portal portal, t_env *env)
{
	if (portal.mat && (env->events.keys[SDL_SCANCODE_KP_0] ||
		env->events.keys[SDL_SCANCODE_0]))
		portal.mat = NULL;
	else if (env->events.keys[SDL_SCANCODE_KP_0] ||
		env->events.keys[SDL_SCANCODE_0])
		portal.mat = env->game.materials;
	env->events.keys[SDL_SCANCODE_KP_0] = 0;
	env->events.keys[SDL_SCANCODE_0] = 0;
	return (portal);
}

t_env			change_material_tool(t_env env, t_selected selected)
{
	t_mat		**m;
	t_portal	portal;

	m = NULL;
	if (selected.type == PART_WALL || (selected.type == PART_PORTAL &&
		(selected.mod == MOD_STEP || selected.mod == MOD_CEIL)))
		m = &env.game.walls[selected.id].mat;
	else if (selected.type == PART_PORTAL && selected.mod == MOD_OPEN)
	{
		if (env.game.portals[env.game.walls[selected.id].portal].mat)
			m = &env.game.portals[env.game.walls[selected.id].portal].mat;
	}
	else if (selected.type == PART_FLOOR)
		m = &env.game.sectors[selected.id].floor_mat;
	else if (selected.type == PART_CEILING)
		m = &env.game.sectors[selected.id].ceiling_mat;
	if (m != NULL && *m != NULL)
		*m = change(*m, &env);
	if (selected.type == PART_PORTAL)
	{
		portal = env.game.portals[env.game.walls[selected.id].portal];
		portal = link_unlink_opening(portal, &env);
		env.game.portals[env.game.walls[selected.id].portal] = portal;
	}
	return (env);
}
