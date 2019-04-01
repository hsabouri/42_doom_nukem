/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_save.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:42:52 by hugo              #+#    #+#             */
/*   Updated: 2019/04/01 16:22:02 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SAVE_H
# define LOAD_SAVE_H

# include <structure.h>
# include <structure_clone.h>
# include <sys/types.h>
// # include <dirent.h>

# define WHITE		(t_color){255,255,255,255}
# define GREY		(t_color){128,128,128,255}
# define RED		(t_color){255,0,0,255}
# define GREEN		(t_color){0,255,0,255}
# define BLUE		(t_color){0,0,255,255}
# define BLACK		(t_color){0,0,0,255}
# define NO_COLOR	(t_color){0,0,0,0}

typedef	struct dirent t_dirent;
typedef struct stat t_stat;

typedef	enum	e_audio
{
	MUSIC,
	SOUND
}				t_audio;

typedef struct	s_save
{
	size_t	index;
	size_t	max;
}				t_save;

typedef struct s_save_music
{
	DIR			*drt;
	t_dirent	*read;
	char		*path;
	void		*file;
	size_t		size;
	size_t		old_size;
	size_t		loc_content;
	t_stat		st;
	t_audio		type;
}				t_save_music;


void			save(const char *filename, t_game game);
t_game			load(const char *filename, int edit_mode);

t_game			default_map(void);
void			*dump_struct(void *buf, size_t start, size_t size, size_t max);
void			verify_magic(void *t_c_struct, size_t magic, size_t index);
t_player		player_default(void);
t_entity		entity_default(void);

void			write_struct(void *struc, int fd, size_t size);
void			write_mats(int fd, t_mat *mats, size_t nmats, t_img *textures);
void			write_points(int fd, t_vec2 *points, size_t npoints);
void			write_walls(int fd, t_wall *walls, size_t nwalls, t_mat	*mats);
void			write_sectors(int fd, t_sector *sectors, size_t nsectors,\
t_mat *mats);
void			write_portals(int fd, t_portal *portals, size_t nportals,\
t_mat *mats);
void			translate_entity(int fd, t_entity *entities, size_t nentities,\
t_mat *mats);
void			write_weapons(int fd, t_weapon *weapons, size_t nentities,\
t_img *textures);
size_t			write_textures(int fd, t_img *textures, size_t ntextures,\
int index);
size_t			write_audio(int fd, int index, t_audio type);
void			write_music(int fd, t_audio type);

t_img			*parse_textures(void *buf, t_save save, size_t n_entities);
t_mat			*parse_mats(void *buf, t_save save, t_img *texture,\
size_t n_entities);
t_vec2			*parse_points(void *buf, t_save save, size_t n_entities);
t_wall			*parse_walls(void *buf, t_save save, t_mat *mats,\
size_t n_entities);
t_sector		*parse_sectors(void *buf, t_save save, t_mat *mats,\
size_t n_entities);
t_portal		*parse_portals(void *buf, t_save save, size_t n_entities,\
t_mat *mats);
t_entity		*parse_entities(void *buf, t_save save, t_mat *mats,\
size_t n_entities);
t_weapon		*parse_weapons(void *buf, t_save save, t_img *textures,\
size_t n_entities);
void			parse_audio(void *buf, t_save save, size_t n_entities,\
t_audio);

int				main_save(char *name);
#endif
