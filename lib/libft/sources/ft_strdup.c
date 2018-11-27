/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:03:45 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/06 13:31:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *dst;

	if ((dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		ft_strcpy(dst, s1);
	else
		return (NULL);
	return (dst);
}
