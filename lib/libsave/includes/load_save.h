/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_save.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:42:52 by hugo              #+#    #+#             */
/*   Updated: 2018/12/29 17:55:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SAVE_H
# define LOAD_SAVE_H

# include <structure.h>
# include <structure_clone.h>

void		save(const char *filename, t_game game);
t_game		load(const char *filename);
t_player	player_default(void);

#endif
