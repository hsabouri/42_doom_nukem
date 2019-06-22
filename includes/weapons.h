/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:12:07 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/22 18:32:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPONS_H
# define WEAPONS_H

typedef enum		e_weapon_type
{
	W_GUN = 0,
	W_SMG = 1,
	W_SHOTGUN = 2,
	W_REVOLVER = 3,
	W_NYAN_GUN = 4,
	W_AMMO = 5
}					t_weapon_type;

typedef	enum		e_shot_type
{
	HITSCAN,
	SHOTS,
	STATIC,
	MELEE,
}					t_shot_type;

typedef struct		s_weapon
{
	t_weapon_type	name;
	u_int32_t		type;
	u_int32_t		ammo;
	u_int32_t		ammo_max;
	u_int32_t		damage;
	u_int32_t		cadence;
	t_shot_type		type_shot;
	int				explosion;
	t_array			sprite;
	u_int32_t		decal;
}					t_weapon;

#endif
