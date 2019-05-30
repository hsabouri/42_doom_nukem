/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_sprite_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:45:45 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/30 18:45:48 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_array	sprite_10(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[42];
	apush(&sprite, &material);
	return (sprite);
}

t_array	sprite_11(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[43];
	apush(&sprite, &material);
	return (sprite);
}

t_array	sprite_12(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[44];
	apush(&sprite, &material);
	return (sprite);
}

t_array	sprite_13(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 1, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[45];
	apush(&sprite, &material);
	return (sprite);
}
