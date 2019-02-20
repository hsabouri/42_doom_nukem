/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_measure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:05:23 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/20 12:10:45 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./time_measure.h"

inline double	start_timer(void)
{
	return ((double)clock());
}

inline double	end_timer(double start)
{
	return ((double)(clock() - start) / CLOCKS_PER_SEC);
}
