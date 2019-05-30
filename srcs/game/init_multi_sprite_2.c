/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_sprite_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:59:03 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/30 16:59:06 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_array	sprite_5(t_mat *mats)
{
	t_array	sprite;
	t_mat	*material;

	material = NULL;
	sprite = safe_anew(NULL, 8, sizeof(t_mat *), "init_multi_sprite");
	material = &mats[30];
	apush(&sprite, &material);
	material = &mats[31];
	apush(&sprite, &material);
	material = &mats[32];
	apush(&sprite, &material);
	material = &mats[33];
	apush(&sprite, &material);
	material = &mats[34];
	apush(&sprite, &material);
	material = &mats[35];
	apush(&sprite, &material);
	material = &mats[36];
	apush(&sprite, &material);
	material = &mats[37];
	apush(&sprite, &material);
	return (sprite);
}