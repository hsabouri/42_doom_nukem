/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:58:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/15 17:00:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIGGERS_H
# define TRIGGERS_H

# include <doom.h>

int		no_trigger(t_trigger trigger, t_trigger c_log);
int		see_trigger(t_trigger trigger, t_trigger c_log);
int		touch_trigger(t_trigger trigger, t_trigger c_log);
int		interact_trigger(t_trigger trigger, t_trigger c_log);
int		sector_trigger(t_trigger trigger, t_trigger c_log);

#endif
