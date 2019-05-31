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
		return (ft_strcpy(dst, "Player"));
	else if (type == GUN_MARINE)
		return (ft_strcpy(dst, "Gun marine"));
	else if (type == SMG_MARINE)
		return (ft_strcpy(dst, "Smg marine"));
	else if (type == BLACK_MARINE)
		return (ft_strcpy(dst, "Black marine"));
	else if (type == RED_MARINE)
		return (ft_strcpy(dst, "Red marine"));
	else if (type == GREEN_KEY_CARD)
		return (ft_strcpy(dst, "Green key card"));
	else if (type == BLUE_KEY_CARD)
		return (ft_strcpy(dst, "Blue key card"));
	else if (type == RED_KEY_CARD)
		return (ft_strcpy(dst, "Red key card"));
	else if (type == PURPLE_KEY_CARD)
		return (ft_strcpy(dst, "Purple key card"));
	else if (type == APPLE)
		return (ft_strcpy(dst, "Apple"));
	else if (type == FISH)
		return (ft_strcpy(dst, "Fish"));
	else if (type == MEAT)
		return (ft_strcpy(dst, "Meat"));
	else if (type == MEDIPACK)
		return (ft_strcpy(dst, "Medipack"));
	else if (type == AMMO)
		return (ft_strcpy(dst, "Ammo"));
	else
		return (ft_strcpy(dst, "Unknown"));
}
