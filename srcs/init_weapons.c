/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:50:54 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/11 13:50:55 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a supprimer a fin projet

#include <doom.h>

t_array	init_sprite_gun(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[17];
	apush(&ret, &material);
	material = &textures[18];
	apush(&ret, &material);
	material = &textures[19];
	apush(&ret, &material);
	material = &textures[20];
	apush(&ret, &material);
	material = &textures[21];
	apush(&ret, &material);
	material = &textures[22];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_smg(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[23];
	apush(&ret, &material);
	material = &textures[24];
	apush(&ret, &material);
	material = &textures[25];
	apush(&ret, &material);
	material = &textures[26];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_shotgun(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[27];
	apush(&ret, &material);
	material = &textures[28];
	apush(&ret, &material);
	material = &textures[29];
	apush(&ret, &material);
	material = &textures[30];
	apush(&ret, &material);
	material = &textures[31];
	apush(&ret, &material);
	material = &textures[32];
	apush(&ret, &material);
	material = &textures[33];
	apush(&ret, &material);
	material = &textures[34];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_revolver(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[35];
	apush(&ret, &material);
	material = &textures[36];
	apush(&ret, &material);
	material = &textures[37];
	apush(&ret, &material);
	material = &textures[38];
	apush(&ret, &material);
	material = &textures[39];
	apush(&ret, &material);
	material = &textures[40];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_nyan_gun(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[41];
	apush(&ret, &material);
	material = &textures[42];
	apush(&ret, &material);
	material = &textures[43];
	apush(&ret, &material);
	material = &textures[44];
	apush(&ret, &material);
	material = &textures[45];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_grenade(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[46];
	apush(&ret, &material);
	material = &textures[47];
	apush(&ret, &material);
	return (ret);
}

t_array	init_sprite_mine(t_img *textures)
{
	t_array ret;
	t_img	*material;

	ret = safe_anew(NULL, 1, sizeof(t_img *), "generate_map");
	material = &textures[48];
	apush(&ret, &material);
	material = &textures[49];
	apush(&ret, &material);
	return (ret);
}