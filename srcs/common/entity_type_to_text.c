/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_type_to_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:02:20 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/05 10:17:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure.h>

static char	*type_to_text_3(t_entity_type type, char *dst)
{
	if (type == CEIL_LAMP)
		return (ft_strcpy(dst, "Ceil lamp"));
	else if (type == PLANT_2)
		return (ft_strcpy(dst, "Plant 2"));
	else if (type == PLANT_3)
		return (ft_strcpy(dst, "Plant 3"));
	else if (type == PLANT_4)
		return (ft_strcpy(dst, "Plant 4"));
	else if (type == TRASH_1)
		return (ft_strcpy(dst, "Trash 1"));
	else if (type == TRASH_2)
		return (ft_strcpy(dst, "Trash 2"));
	else if (type == GUN)
		return (ft_strcpy(dst, "Gun"));
	else if (type == SMG)
		return (ft_strcpy(dst, "SMG"));
	else if (type == SHOTGUN)
		return (ft_strcpy(dst, "Shotgun"));
	else if (type == REVOLVER)
		return (ft_strcpy(dst, "Revolver"));
	else if (type == NYAN_GUN)
		return (ft_strcpy(dst, "Nyan-gun"));
	else
		return (ft_strcpy(dst, "Unknown"));
}

static char	*type_to_text_2(t_entity_type type, char *dst)
{
	if (type == MEAT)
		return (ft_strcpy(dst, "Meat"));
	else if (type == MEDIPACK)
		return (ft_strcpy(dst, "Medipack"));
	else if (type == AMMO)
		return (ft_strcpy(dst, "Ammo"));
	else if (type == CLOSE_RED)
		return (ft_strcpy(dst, "Close red"));
	else if (type == CLOSE_BLUE)
		return (ft_strcpy(dst, "Close blue"));
	else if (type == CLOSE_GREEN)
		return (ft_strcpy(dst, "Close green"));
	else if (type == CLOSE_PURPLE)
		return (ft_strcpy(dst, "Close purple"));
	else if (type == OPEN_RED)
		return (ft_strcpy(dst, "Open red"));
	else if (type == OPEN_BLUE)
		return (ft_strcpy(dst, "Open blue"));
	else if (type == OPEN_GREEN)
		return (ft_strcpy(dst, "Open green"));
	else if (type == OPEN_PURPLE)
		return (ft_strcpy(dst, "Open purple"));
	else if (type == LAMP)
		return (ft_strcpy(dst, "Lamp"));
	return (type_to_text_3(type, dst));
}

char		*type_to_text(t_entity_type type, char *dst)
{
	if (type == PLAYER)
		return (ft_strcpy(dst, "Player"));
	else if (type == GUN_MARINE)
		return (ft_strcpy(dst, "Gun marine"));
	else if (type == SMG_MARINE)
		return (ft_strcpy(dst, "Smg marine"));
	else if (type == RACLURE)
		return (ft_strcpy(dst, "Raclure"));
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
	else if (type == PLANT_1)
		return (ft_strcpy(dst, "Plant 1"));
	else if (type == APPLE)
		return (ft_strcpy(dst, "Apple"));
	else if (type == FISH)
		return (ft_strcpy(dst, "Fish"));
	return (type_to_text_2(type, dst));
}
