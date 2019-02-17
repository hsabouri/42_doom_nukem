/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_id.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:32:13 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/17 11:23:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATE_ID_H
# define TRANSLATE_ID_H

# include <sys/types.h>
# include <unistd.h>

# define ID_PART_MASK 0x7
# define ID_PART_SHIFT 0
# define ID_MOD_MASK 0x18
# define ID_MOD_SHIFT 3
# define ID_SPARE_MASK 0xE0
# define ID_SPARE_SHIFT 5
# define ID_ID_MASK 0xFFFFFF00
# define ID_ID_SHIFT 8

typedef enum	e_mod
{
	MOD_NO = 0x0,
	MOD_STEP = 0x1,
	MOD_CEIL = 0x2,
	MOD_OPEN = 0x3
}				t_mod;

typedef enum	e_part
{
	PART_FLOOR = 0x1,
	PART_CEILING = 0x2,
	PART_WALL = 0x3,
	PART_PORTAL = 0x4,
	PART_ENTITY = 0x5,
	PART_NO = 0x0
}				t_part;

typedef struct	s_selected
{
	t_part		type;
	t_mod		mod;
	ssize_t		id;
	char		spare;
}				t_selected;

u_int32_t		translate_in(t_part part, t_mod mod, size_t id, char spare);
t_selected		translate_out(u_int32_t serial);

#endif
