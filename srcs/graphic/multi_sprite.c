/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:29:01 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 17:59:44 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./multi_sprite.h"

t_mat	*choose_entity_material(t_entity entity, t_vec2 pos)
{
	t_vec2	cossin;
	t_vec2	look;
	t_vec2	perp;
	t_mat	*mat;
	int		img;

	pos = vec2_normalize(vec2_sub(vec3_to_vec2(entity.physic.pos), pos));
	look = vec2_rot(vec2_new(0, 1), entity.physic.look_h);
	perp = vec2_rot(vec2_new(1, 0), entity.physic.look_h);
	cossin.u = vec2_cross(pos, look).z;
	cossin.v = vec2_cross(pos, perp).z;
	if (cossin.v >= 0)
		img = (entity.mat->len / 4) + cossin.u * (entity.mat->len / 4);
	else
		img = (3 * entity.mat->len / 4) - cossin.u * (entity.mat->len / 4);
	mat = *(t_mat **)anth(entity.mat, img % entity.mat->len);
	return (mat);
}
