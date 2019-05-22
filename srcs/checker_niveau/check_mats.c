/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:28:12 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/21 16:51:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error	check_multi_sprite(t_lvl_error error, size_t nmulti, t_array *multi_sprite,\
t_mat *mats, size_t nmaterials)
{
	size_t		cpt;
	t_mat		**material;
	size_t		i;
	u_int32_t	index;
	
	cpt = 0;
	while (cpt < nmulti)
	{
		i = 0;
		while (i < multi_sprite[cpt].len)
		{
			material = anth(&multi_sprite[cpt], i);
			index = id_from_p(*material, mats, sizeof(t_mat));
			if (material != NULL && index >= nmaterials)
			{
				error.error_type = MULTI_SPRITE;
				error.mats = i;
				error.multi_mats = cpt;
				return (error);
			}
			i++;
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	check_texture(t_lvl_error error, size_t ntextures, t_img *textures,\
t_check_mat mats)
{
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	while (cpt < mats.nmaterials)
	{
		index = id_from_p(mats.materials[cpt].texture, textures, sizeof(t_img));
		if (index >= ntextures && mats.materials[cpt].texture != NULL)
		{
			error.error_type = TEXTURES_MAT;
			error.mats = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	check_overlay(t_mat *materials, t_lvl_error error,\
size_t nmaterials)
{
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	while (cpt < nmaterials)
	{
		index = id_from_p(materials[cpt].overlay, materials, sizeof(t_mat));
		if (index >= nmaterials && materials[cpt].overlay != NULL)
		{
			error.error_type = OVERLAY_MAT;
			error.mats = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

u_int32_t	launch_check_mats(t_lvl_error error, t_game game,\
char *errors_text[NBR_ERROR], t_check_mat mats, t_env *env)
{
	error = check_texture(error, game.ntextures, game.textures, mats);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: material %d\n", errors_text[error.error_type],
			error.mats);
		return (check_editor(env));
	}
	error = check_overlay(game.materials, error, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: material %d\n", errors_text[error.error_type],
			error.mats);
		return (check_editor(env));
	}
	error = check_multi_sprite(error, game.nmulti_mats, game.multi_mats,\
		game.materials, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: %d, material %d\n", errors_text[error.error_type],
			error.multi_mats, error.mats);
		return (check_editor(env));
	}
	return (1);
}
