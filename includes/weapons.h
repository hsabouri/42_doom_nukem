/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:12:07 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/03 17:12:09 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPONS_H
# define WEAPONS_H

typedef enum		e_weapon_type
{
	GUN,
	SMG,
	SHOTGUN,
	REVOLVER,
	NYAN_GUN,
	KNIFE,
	GRENADE,
	MINE,
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
