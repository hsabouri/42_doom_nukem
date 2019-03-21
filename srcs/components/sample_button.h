/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_button.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:49:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/21 14:05:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_BUTTON_H
# define SAMPLE_BUTTON_H

# include <editor.h>

int			button_update(t_component *self, void *elem);
void		button_render(const t_component self, t_color *buf);
t_component	init_button(char *str, t_sdl *sdl);

#endif