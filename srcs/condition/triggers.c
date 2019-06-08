/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:58:01 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/08 16:10:39 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

int    shot_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_SHOT && trigger.condi == c_log.condi &&
		trigger.e_actif.id == c_log.e_actif.id &&
		trigger.e_passif.id == c_log.e_passif.id)
		return 1;
	return 0;
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

// int      interact_n_press_trigger(t_trigger trigger, t_trigger c_log)
// {
// 	if (trigger.condi == TRIGGER_INTER_PRESS && trigger.condi == c_log.condi &&
// 		trigger.e_actif.id == c_log.e_actif.id &&
// 		trigger.e_passif.id == c_log.e_passif.id)
// 		return 1;
// 	return 0;
// }

int      sector_trigger(t_trigger trigger, t_trigger c_log)
{
	if (trigger.condi == TRIGGER_SECTOR && trigger.condi == c_log.condi
		&& trigger.e_actif.physic.sector_id == c_log.e_actif.physic.sector_id)
		return (1);
	return (0);
}
