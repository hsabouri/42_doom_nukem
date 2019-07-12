/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:25:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static void		launch_game2(t_env *env)
{
	env->game.animations = safe_anew(NULL, 10, sizeof(t_animation), "init");
	env->game.col_events = safe_anew(NULL, 10, sizeof(t_col_event), "init");
	env->game.weapons = init_weapons(&env->game);
	launch_check(env, env->game);
	env->game.id_buf = (u_int32_t *)safe_malloc((WIDTH * HEIGHT
	* sizeof(int)), "doom_nukem");
	if (env->component)
	{
		destroy_component(env->component);
		free(env->component);
	}
	find_center_sectors(env->game);
	env->component = init_component(env, &env->sdl);
	env->init_game = 0;
}

static void		launch_game(t_env *env, int ac, char **av)
{
	t_game		*ret_load;

	if (ac == 2)
	{
		if ((ret_load = load(av[1], env->editor.enabled)) != NULL)
		{
			env->game = *ret_load;
			free(ret_load);
		}
		else
			env->game = generate_map();
	}
	else
		env->game = generate_map();
	env->game = init_audio(env->game);
	launch_game2(env);
}

static void		all_loops(t_env *env, size_t frame)
{
	if (env->game_mode == MENU_MODE)
		menu_loop(env);
	else if (env->game_mode == GAME_MODE)
	{
		if (!env->toggle_editor)
			game_loop(env, frame);
		else
			editor_loop(env);
	}
	else if (env->game_mode == DEAD)
		dead_loop(env);
	if (!env->sdl.win)
	{
		console_error("doom_nukem", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

static void		first_init(t_env *env, int ac, char **av)
{
	if (ac == 2)
		env->file = av[1];
	else
		env->file = NULL;
	env->sdl = init_sdl();
	env->editor = init_editor();
	env->toggle_editor = 0;
	env->events = init_events();
	env->game_mode = MENU_MODE;
	env->init_game = 1;
	env->component = init_menu(env, &env->sdl);
	*env->component = render_all(*env->component, &env->sdl);
	env->game_mode = 0;
	env->init_game = 1;
}

int				main(int ac, char **av)
{
	t_env		env;
	size_t		frame;

	first_init(&env, ac, av);
	frame = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (env.sdl.win)
	{
		env.events = capture_events(env.events, &env);
		if (env.init_game && env.game_mode == GAME_MODE)
			launch_game(&env, ac, av);
		if (!env.toggle_editor)
			env.game.player.my_entity.physic = update_mouse(&env.events,
				env.game.player.my_entity.physic);
		if (env.events.quit || env.game_mode == QUIT
			|| env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		all_loops(&env, frame);
		env.events = reset_clicks(env.events);
		frame++;
	}
	if (env.game_mode != 0)
		clean_game(env.game);
	return (0);
}
