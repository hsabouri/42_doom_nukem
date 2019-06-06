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

static t_lvl_error	check_multi_sprite(size_t nmulti, t_array *multi_sprite,
t_mat *mats, size_t nmaterials)
{
	t_lvl_error	error;
	size_t		cpt;
	t_mat		**material;
	size_t		i;
	u_int32_t	index;

	cpt = -1;
	init_error(&error);
	while (++cpt < nmulti)
	{
		i = -1;
		while (++i < multi_sprite[cpt].len)
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
		}
	}
	return (error);
}

static t_lvl_error	check_texture(size_t ntextures, t_img *textures,
t_check_mat mats)
{
	t_lvl_error	error;
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	init_error(&error);
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

static t_lvl_error	check_overlay(t_mat *materials, size_t nmaterials)
{
	t_lvl_error	error;
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	init_error(&error);
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

static u_int32_t	launch_check_mats_2(t_game game, t_env *env,
char *errors_text[NBR_ERROR])
{
	t_lvl_error error;

	error = check_multi_sprite(game.nmulti_mats, game.multi_mats,
		game.materials, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": material ");
		ft_putnbr(error.multi_mats);
		ft_putchar('\n');
		return (check_editor(env));
	}
	return (1);
}

u_int32_t			launch_check_mats(t_game game, t_check_mat mats, t_env *env,
char *errors_text[NBR_ERROR])
{
	t_lvl_error error;

	error = check_texture(game.ntextures, game.textures, mats);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": material ");
		ft_putnbr(error.mats);
		ft_putchar('\n');
		return (check_editor(env));
	}
	error = check_overlay(game.materials, game.nmaterials);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": material ");
		ft_putnbr(error.mats);
		ft_putchar('\n');
		return (check_editor(env));
	}
	launch_check_mats_2(game, env, errors_text);
	return (1);
}
