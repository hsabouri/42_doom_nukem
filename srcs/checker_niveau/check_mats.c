/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:28:12 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/25 12:28:17 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error	check_texture(t_lvl_error error, size_t ntextures, t_img *textures,\
t_check_mat mats)
{
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	while (cpt < mats.nmaterials)
	{
		index = id_from_p(mats.materials[cpt].texture, textures, sizeof(t_img));
		if (index > ntextures && mats.materials[cpt].texture != NULL)
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
		if (index > nmaterials && materials[cpt].overlay != NULL)
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
char *errors_text[NBR_ERROR], t_check_mat mats)
{
	error = check_texture(error, game.ntextures, game.textures, mats);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: material %zu\n", errors_text[error.error_type],
			error.mats);
		return (0);
	}
	error = check_overlay(game.materials, error, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: material %zu\n", errors_text[error.error_type],
			error.mats);
		return (0);
	}
	return (1);
}
