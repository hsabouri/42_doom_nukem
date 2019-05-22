/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:29:34 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/21 15:29:36 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	init_error(t_lvl_error *error)
{
	error->error_type = NO_ERROR;
	error->point = -1;
	error->wall = -1;
	error->portal = -1;
	error->sector = -1;
	error->mats = -1;
	error->multi_mats = -1;
	error->entities = -1;
}

int		check_editor(t_env *env)
{
	if (env->editor.enabled && env->toggle_editor == 1)
		return (0);
	else
		exit(EXIT_FAILURE);
	return (1);
}
