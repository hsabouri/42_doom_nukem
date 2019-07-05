/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:58:19 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/05 10:20:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

void	destroy_button(t_component *self)
{
	t_button_state *state;

	state = (t_button_state *)self->state;
	if (state->img_active.content)
		free(state->img_active.content);
	free(state);
}

void	destroy_button_ft(t_component *self)
{
	t_button_ft_state *state;

	state = (t_button_ft_state *)self->state;
	if (state->img_active.content)
		free(state->img_active.content);
	free(state);
}

void	destroy_cb_button(t_component *self)
{
	t_cb_button_state *state;

	state = (t_cb_button_state *)self->state;
	if (state->img_active.content)
		free(state->img_active.content);
	free(state);
}
