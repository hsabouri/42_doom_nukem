/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:10:36 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/06 11:52:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	n;
	char	*ptr;

	n = ft_strlen(s);
	if (c == 0)
		ptr = ((char *)s) + n;
	else
		ptr = ft_memchr(s, c, n);
	return (ptr);
}
