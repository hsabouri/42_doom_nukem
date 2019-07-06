/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:26:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 13:10:16 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure.h>

t_game		animate(t_game game, float old_timer)
{
	const float	span = old_timer;
	t_array		new_array;
	t_animation	*current;

	if (game.animations.len == 0)
		return (game);
	new_array = anew(NULL, ((game.animations.len > 10) ?
		game.animations.len : 10), sizeof(t_animation));
	while ((current = (t_animation *)apop(&game.animations)))
	{
		if (fabs(current->target - *current->to_animate)
			< ANIMATION_SPEED * span)
			*current->to_animate = current->target;
		else if (current->target > *current->to_animate)
			*current->to_animate += ANIMATION_SPEED * span;
		else
			*current->to_animate -= ANIMATION_SPEED * span;
		if (fabs(current->target - *current->to_animate) > 0.001)
			apush(&new_array, current);
		else
			*current->to_animate = current->target;
	}
	free(game.animations.mem);
	game.animations = new_array;
	return (game);
}
