/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2019/04/26 13:06:48 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <float.h>

# include <libft.h>
# include <vec.h>
# include <graphic.h>
# include <physic.h>

# include <load_save.h>
// # include <structure_clone.h>

# include <checker.h>

# include "srcs/common/translate_id.h"

# define N_KEY 284
# define N_BUTTON 5

# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)

# define LOOK_SPEED 0.01

# define NB_TEXT 	100

# ifdef __linux
#  define ON_LINUX 1
# else
#  define ON_LINUX 0
# endif

typedef	enum	e_game_mode
{
	MENU_MODE,
	GAME_MODE,
	QUIT
}				t_game_mode;

typedef int (*ft_trigger)(t_trigger trigger, t_trigger c_log);

typedef struct			s_event
{
	int			any;
	int16_t		x;
	int16_t		y;
	int16_t		old_x;
	int16_t		old_y;
	int16_t		wheel;
	u_int8_t	quit;
	u_int8_t	mouse[N_BUTTON];
	u_int8_t	mouse_click[N_BUTTON];
	u_int8_t	keys[N_KEY];
	u_int8_t	key_click[N_KEY];
}						t_event;

typedef struct	s_text
{
	int16_t		x;
	int16_t		y;
	int32_t		w;
	int32_t		h;
	SDL_Texture	*text_texture;
}				t_text;

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	t_array			text;
}						t_sdl;

typedef struct	s_component_event
{
    int hover;
    // potentiellement + plus tard
}				t_component_event;

typedef struct	s_component
{
	int				display;
    t_pix 			pos;
	t_pix			size;
    t_text			text;
    t_img			img;
    void			*state;
    void			(*render)(struct s_component self, t_color *buf);
    SDL_Texture		*(*complete_render)(struct s_component self, t_sdl *sdl);
    int				(*update)(struct s_component *self, void *state);
	void			(*destroy)(struct s_component *self);
    t_array			childs;
	SDL_Texture		*last_render;
}				t_component;

typedef enum	e_tool
{
	POINT = 0,
	WALL = 1,
	PORTAL = 2
}				t_tool;

typedef enum	e_game_tool
{
	TEXTURE_MOVE = 0,
	MATERIAL_MOVE = 1,
	MATERIAL_SCALE = 2,
	SECTOR_HEIGHT = 3,
	MATERIAL_CHANGE = 4,
	TOOL_NO
}				t_game_tool;

struct			s_env;

typedef struct	s_editor
{
	int				enabled;
	float			zoom;
	t_vec2			offset;
	t_tool			current_tool;
	t_game_tool		game_tool;
	struct s_env	(*tools[3])(struct s_env);
	struct s_env	(*game_tools[10])(struct s_env, t_selected);
	ssize_t			sel_point;
	ssize_t			sel_wall;
	ssize_t			points_wall[2];
	uint8_t			depth;
	int				selecting;
}				t_editor;

typedef struct			s_env
{
	char		*file;
	t_game		game;
	int			toggle_editor;
	t_game_mode	game_mode;
	int			init_game;
	t_editor	editor;
	t_color		*current_buffer;
	t_component	*component;
	t_sdl		sdl;
	ft_trigger	*condition;
	t_event		events; //must be last
	
}						t_env;

int						is_clicked_on(const t_component component, t_event events);
int						is_over(const t_component component, t_event events);
void					m_background(t_color *buf, t_color color, t_pix start, t_pix end);
t_game					init_audio(t_game game);

t_component				default_component(void *state_address, t_pix size, t_sdl *sdl);
t_component     		*init_component(t_env *env, t_sdl *sdl);
t_component				trigger_component(void *parent, t_component component, t_sdl *sdl);
void					display_component(const t_component component, t_sdl *sdl);
void					destroy_component(t_component *component);
void					clean_childs(t_array childs);
t_component				render_all(t_component component, t_sdl *sdl);

t_text					component_text(const char *str, t_pix pos, t_sdl *sdl);
void					component_image(const t_img img, t_pix pos,
						const t_pix buf_size, t_color *buf);

SDL_Texture				*empty_render(t_component any, t_sdl *sdl);
void					no_destroy(t_component *self);

t_env					game_loop(t_env env, size_t frame);
t_env					editor_loop(t_env env);

t_event					capture_events(t_event events, t_env *env);
t_event					init_events(void);
t_ph					update_mouse(t_event *events, t_ph player_physic);
t_event					reset_clicks(t_event events);

void					bresenham(t_color *buff, t_pix a, t_pix b, \
						t_color color);

t_game					physic(t_game game, t_event events, float old_timer);

t_text					text(const char *str, t_pix pos, t_sdl *sdl);

// lib save fc a retirer une fois corriger
size_t	id_from_p(void *ptr, void *tab, size_t size);

void		*id_to_p(ssize_t index, void *tab, size_t size);
//

/*
** CONDITION
*/

t_env	init_conditions(t_env env);
t_game  check_conditions(t_game game, t_event events, ft_trigger *triggers);
t_game 	ft_reset_log(t_game game);

ssize_t					select_wall(t_game game, t_editor editor,\
						t_event events);
t_editor				select_multi_points(t_editor editor,\
						t_event events, ssize_t point);
void					legend_text(t_sdl sdl);
void					legend_graphic(t_color *buf);
t_game					player_properties(t_game game, t_event events);

void					play_music(t_game game, size_t id, size_t vol, size_t frame);	
t_array					stack_sounds(t_array chunk, size_t id, u_int32_t vol);
t_game					play_sounds(t_game game);

void					render_multi_threaded(const t_env env, t_color *buf);
void					render_single_threaded(const t_env env, t_color *buf);

void					*safe_malloc(size_t size, char *location);
void					*safe_realloc(void *ptr, size_t size, char *location);
t_array					safe_anew(void *first, size_t len, size_t elem_size,\
						char *location);

void					clean_music(t_game game);
void					clean_env(t_env env);
void					clean_game(t_game game);
void					clean_texture(t_env env);

t_component				*init_menu(t_env *env, t_sdl *sdl);
t_env					menu_loop(t_env env);

void					minimap(t_game game, t_color *buf);

// a enlever a fin projet
t_array					init_sprite_gun();
t_array					init_sprite_smg();
t_array					init_sprite_shotgun();
t_array					init_sprite_revolver();
t_array					init_sprite_nyan_gun();
t_array					init_sprite_grenade();
t_array					init_sprite_mine();

#endif
