/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_type_to_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:02:20 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/22 12:12:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure.h>

char	*type_to_text(t_entity_type type, char *dst)
{
	if (type == PLAYER)
		return (ft_strcpy(dst, "player"));
	else if (type == GROSSE_DAME)
		return (ft_strcpy(dst, "grosse dame"));
	else if (type == KEY_CARD)
		return (ft_strcpy(dst, "key card"));
	else
		return (ft_strcpy(dst, "unknown"));
}
