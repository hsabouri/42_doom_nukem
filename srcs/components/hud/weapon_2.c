/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:52:33 by fmerding          #+#    #+#             */
/*   Updated: 2019/06/22 18:54:39 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

char	*self_2(char *str, int ammo)
{
	char *tmp;

	str = ft_itoa(ammo);
	tmp = str;
	str = ft_strjoin(str, "/");
	ft_strdel(&tmp);
	return (str);
}
