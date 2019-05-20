/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:20:35 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/20 17:57:34 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure.h>

t_game		animate(t_game game, float old_timer)
{
	const float	span = old_timer;
	t_array		new_array;
	t_animation	*current;
	size_t		i;

	i = 0;
	new_array = anew(NULL, game.animations.len, sizeof(t_animation));
	while ((current = (t_animation *)anth(&game.animations, i)))
	{
		if (ABS(current->target - *current->to_animate) < ANIMATION_SPEED * span)
			*current->to_animate = current->target;
		if (current->target > *current->to_animate)
			*current->to_animate += ANIMATION_SPEED * span;
		else
			*current->to_animate -= ANIMATION_SPEED * span;
		if (ABS(current->target - *current->to_animate) > 0.01)
			apush(&new_array, current);
		i++;
	}
	free(game.animations.mem);
	game.animations = new_array;
	return (game);
}
