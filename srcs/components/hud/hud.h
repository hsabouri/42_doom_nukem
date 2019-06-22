/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:22:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/22 18:54:45 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../root.h"

typedef struct	s_hud_state
{
	t_env *env;
}				t_hud_state;

t_component		init_hud_root(t_env *env, t_sdl *sdl);

typedef struct	s_weapons_state
{
	t_sdl		*sdl;
	t_weapon	*weapons;
	t_player	*player;
	u_int32_t	last_equiped;
	u_int32_t	last_secondary;
	int			shot;
}				t_weapons_state;

typedef struct	s_mini_weapon
{
	void		*parent;
	u_int32_t	last_ammo;
	t_text		str;
}				t_mini_weapon;

typedef struct	s_life_state
{
	t_env		*env;
	t_color		background;
	t_player	*player;
	float		last_life;
	t_img		empty_life;
	t_pix		pos;
	u_int32_t	display;
	t_sdl		*sdl;
}				t_life_state;

typedef struct	s_inventory_state
{
	t_array		*inventory_state;
	int			is_active;
	int			is_display;
	t_color		background;
	t_game		*game;
}				t_inventory_state;

typedef struct	s_help_comp_state
{
	t_img		help;
	t_img		help_ig_edit;
	int			is_active;
	int			is_display;
	int			img_display;
	t_color		background;
}				t_help_comp_state;

t_array			init_weapon(t_array array, void *parent_state, t_sdl *sdl);
t_array			mini_weapon(t_array array, void *parent_state, t_sdl *sdl);
t_array			mini_weapon_s(t_array array, void *parent_state,
t_sdl *sdl);
t_array			init_life(t_array array, void *parent_state, t_sdl *sdl);
t_array			init_full_life(t_array array, void *parent_state, t_sdl *sdl);
t_array			init_empty_life(t_array array, void *parent_state, t_sdl *sdl);
t_array			init_inventory(t_array array, void *parent_state, t_sdl *sdl);
t_array			init_help(t_array array, void *parent_state, t_sdl *sdl);
t_array			init_cross(t_array childs, void *parent_state, t_sdl *sdl);
t_array			init_mini_map(t_array array, void *parent_state, t_sdl *sdl);
char			*self_2(char *str, int ammo);

#endif
