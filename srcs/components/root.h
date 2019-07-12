/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 12:02:38 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:28:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOT_H
# define ROOT_H

# include <editor.h>

t_component		init_dead(t_env *env, t_sdl *sdl);
t_component		init_win(t_env *env, t_sdl *sdl);
t_component		init_root(t_env *env, t_sdl *sdl);

#endif
