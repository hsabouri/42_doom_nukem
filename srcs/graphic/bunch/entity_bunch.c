/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_bunch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:57:01 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 16:11:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include <doom.h>
#include "srcs/graphic/multi_sprite.h"
#include "./singletons.h"

static void		compute_cache(t_bunch_entity_compute s)
{
	const size_t	sector = s.context.sector.sector_id;
	t_cache_entity	current;
	t_fvec2			tmp;

	if (s.game.entities[s.i].physic.sector_id == sector)
	{
		tmp = vec2_to_fvec2(vec2_rot(vec2_new(
			s.game.entities[s.i].physic.radius, 0), s.context.physic.look_h));
		current.a = fvec2_sub(vec2_to_fvec2(
			vec3_to_vec2(s.game.entities[s.i].physic.pos)), s.pos);
		current.dis = fvec2_ssize(current.a);
		current.b = fvec2_add(current.a, tmp);
		current.a = fvec2_sub(current.a, tmp);
		if (is_in_limit(s.limit, take_left(current.a, current.b),
		take_right(current.a, current.b)))
		{
			current.id = s.i;
			current.h = f_from_float(s.game.entities[s.i].physic.pos.z);
			current.physic = s.game.entities[s.i].physic;
			current.mat = choose_entity_material(s.game.entities[s.i],
				vec3_to_vec2(s.context.physic.pos));
			s.entities[*s.nentities] = current;
			++*s.nentities;
		}
	}
}

t_bunch			build_entity_bunch(const t_game game, const t_context context,
const t_limit limit, t_fvec2 pos)
{
	t_bunch			ret;
	size_t			i;
	t_cache_entity	entities[NCACHEENTITY];

	i = -1;
	ret.nentities = 0;
	while (++i != (size_t)-1 && i < game.nentities && i < NCACHEENTITY)
		compute_cache((t_bunch_entity_compute) {game, context, limit, entities,
			pos, i, &ret.nentities});
	if (ret.nentities)
	{
		ret.entities = (t_cache_entity *)safe_malloc(ret.nentities
			* sizeof(t_cache_entity), "rendering");
		memmove(ret.entities, entities, ret.nentities * sizeof(t_cache_entity));
	}
	else
		ret.entities = NULL;
	return (ret);
}

t_render		build_sections_entities(const t_context ctx,
const t_bunch bunch, const t_limit lmts)
{
	t_cache_entity		c;
	t_section_entity	cs;
	t_section_entity	ets[NCACHEENTITY];
	t_render			rdr;

	rdr.nentities = 0;
	while (rdr.nentities < bunch.nentities)
	{
		c = bunch.entities[rdr.nentities];
		cs.entity = c;
		cs.start = get_ray_id(take_left(c.a, c.b), lmts, ctx, ctx.left);
		cs.end = get_ray_id(take_right(c.a, c.b), lmts, ctx, ctx.right);
		ets[rdr.nentities] = cs;
		++rdr.nentities;
	}
	if (rdr.nentities)
	{
		rdr.entities = (t_section_entity *)safe_malloc(rdr.nentities
			* sizeof(t_section_entity), "rendering");
		ft_memmove(rdr.entities, ets, rdr.nentities * sizeof(t_section_entity));
	}
	else
		rdr.entities = NULL;
	return (rdr);
}
