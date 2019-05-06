/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:03:45 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/06 16:59:33 by hsabouri         ###   ########.fr       */
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

char	*ft_memdup(const char *m, size_t size)
{
	char *dst;

	if ((dst = (char *)malloc(sizeof(char) * size)))
		ft_memcpy(dst, m, size);
	else
		return (NULL);
	return (dst);
}
