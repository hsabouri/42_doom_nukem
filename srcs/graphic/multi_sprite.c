/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:29:01 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/11 15:23:50 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./multi_sprite.h"

t_mat	*choose_entity_material(t_entity entity, t_vec2 pos)
{
	float	cosin;
	float	sinus;
	t_vec2	look;
	t_vec2	perp;
	t_mat	*mat;

	pos = vec2_normalize(vec2_sub(vec3_to_vec2(entity.physic.pos), pos));
	look = vec2_rot(vec2_new(0, 1), entity.physic.look_v);
	perp = vec2_rot(vec2_new(1, 0), entity.physic.look_v);
	cosin = vec2_cross(pos, look).z;
	sinus = vec2_cross(pos, perp).z;
	int img;
	if (sinus >= 0)
		img = (entity.mat->len / 4) + cosin * (entity.mat->len / 4);
	else
		img = (3 * entity.mat->len / 4) - cosin * (entity.mat->len / 4);
	mat = *(t_mat **)anth(entity.mat, img % entity.mat->len);
	return (mat);
}
