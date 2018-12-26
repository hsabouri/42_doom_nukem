/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_save.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:42:52 by hugo              #+#    #+#             */
/*   Updated: 2018/12/26 12:45:00 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SAVE_H
# define LOAD_SAVE_H

# include <structure_clone.h>
# include "../../includes/doom.h"

void		save(t_game game, int fd);
void		load(const char *filename);

#endif