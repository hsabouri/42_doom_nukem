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

static int	lievre_tortue(struct s_mat *tortue, struct s_mat *lievre,\
t_mat *materials, size_t cpt)
{	
	ssize_t id_1;
	ssize_t id_2;

	tortue = &materials[cpt];
	id_1 = id_from_p(tortue, materials, sizeof(t_mat));
	lievre = (materials[cpt].overlay->overlay) ?
		materials[cpt].overlay->overlay : NULL;
	id_2 = (!lievre) ? -1 : id_from_p(lievre, materials, sizeof(t_mat));
	while (tortue)
	{
		if (lievre == tortue)
			return (1);
		else if (materials[id_1].overlay && id_2 != -1 && materials[id_2].overlay->overlay)
		{
			tortue = materials[id_1].overlay;
			id_1 = id_from_p(tortue, materials, sizeof(t_mat));
			lievre = materials[id_2].overlay->overlay;
			id_2 = id_from_p(lievre, materials, sizeof(t_mat));
		}
		else
			return (0);
	}
	return (0);
}

t_lvl_error	check_boucle_mat(t_lvl_error error, t_mat *materials,\
size_t nmaterials)
{
	size_t			cpt;
	struct s_mat	*tortue;
	struct s_mat	*lievre;

	cpt = 0;
	while (cpt < nmaterials)
	{
		if (materials[cpt].overlay)
		{
			tortue = NULL;
			lievre = NULL;
			if (lievre_tortue(tortue, lievre, materials, cpt) == 1)
			{
				error.error_type = LOOP_OVERLAY;
				error.mats = cpt;
				return (error);
			}
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
	error = check_boucle_mat(error, game.materials, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: material %zu\n", errors_text[error.error_type],
			error.mats);
		return (0);
	}
	return (1);
}
