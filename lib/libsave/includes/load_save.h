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

typedef struct	s_save
{
	size_t	index;
	size_t	max;
}				t_save;

void			save(const char *filename, t_game game);
t_game			load(const char *filename);
void			*dump_struct(void *buf, size_t start, size_t size, size_t max);
void			verify_magic(void *t_c_struct, size_t magic, size_t index);
t_player		player_default(void);

void			write_struct(void *struc, int fd, size_t size);
void			write_mats(int fd, t_mat *mats, size_t nmats, t_img *textures);
void			write_points(int fd, t_vec2 *points, size_t npoints);
void			write_walls(int fd, t_wall *walls, size_t nwalls, t_mat	*mats);
void			write_sectors(int fd, t_sector *sectors, size_t nsectors,\
t_mat *mats);
void			write_portals(int fd, t_portal *portals, size_t nportals);

t_img			*parse_textures(void *buf, t_save save, size_t n_entities);
t_mat			*parse_mats(void *buf, t_save save, t_img *texture,\
size_t n_entities);
t_vec2			*parse_points(void *buf, t_save save, size_t n_entities);
t_wall			*parse_walls(void *buf, t_save save, t_mat *mats,\
size_t n_entities);
t_sector		*parse_sectors(void *buf, t_save save, t_mat *mats,\
size_t n_entities);
t_portal		*parse_portals(void *buf, t_save save, size_t n_entities);

int				main_save(char *name);
#endif
