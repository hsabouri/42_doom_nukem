/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:58:01 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/15 16:58:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int	no_trigger(t_trigger trigger, t_trigger c_log)
{
	(void)trigger;
	(void)c_log;
	return (1);
}

int	see_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_SEE && trigger.condi == c_log.condi
		&& trigger.e_actif.id == c_log.e_actif.id
		&& trigger.e_passif.id == c_log.e_passif.id)
		return (1);
	return (0);
}

int	touch_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_TOUCH && trigger.condi == c_log.condi
		&& trigger.e_actif.id == c_log.e_actif.id
		&& trigger.e_passif.id == c_log.e_passif.id)
		return (1);
	return (0);
}

int	interact_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_INTERACT && trigger.condi == c_log.condi
		&& trigger.e_actif.id == c_log.e_actif.id
		&& trigger.e_passif.id == c_log.e_passif.id)
		return (1);
	return (0);
}

int	sector_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_SECTOR && trigger.condi == c_log.condi
		&& trigger.e_actif.physic.sector_id == c_log.e_actif.physic.sector_id)
		return (1);
	return (0);
}
