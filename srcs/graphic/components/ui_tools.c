/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 17:08:48 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

int			is_over(const t_component component, t_event events)
{
	if (events.x >= component.pos.x
		&& events.x <= component.pos.x + component.size.x
		&& events.y >= component.pos.y
		&& events.y <= component.pos.y + component.size.y)
		return (1);
	return (0);
}

int			is_clicked_on(const t_component component, t_event events)
{
	if (is_over(component, events) && events.mouse[SDL_BUTTON_LEFT])
		return (1);
	return (0);
}
