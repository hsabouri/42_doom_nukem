/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:05:58 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 18:02:18 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <pthread.h>

static void	*start_render(void *info)
{
	const t_thread_info	thread_info = *(t_thread_info *)info;

	m_background(thread_info.buf, NO_COLOR, (t_pix) {
		thread_info.context.left, 0}, (t_pix) {
		thread_info.context.right, HEIGHT});
	render(thread_info.game, thread_info.context,
		thread_info.buf, thread_info.id_buf);
	return (NULL);
}

void		render_single_threaded(const t_env env, t_color *buf)
{
	background(buf, NO_COLOR, (t_pix){WIDTH, HEIGHT});
	render(env.game,
		(t_context) {
			0,
			WIDTH,
			env.game.player.my_entity.physic,
			-1,
			env.game.sectors[env.game.player.my_entity.physic.sector_id],
			0,
			get_ray_dir(env.game.player.my_entity.physic, 0),
			get_ray_dir(env.game.player.my_entity.physic, WIDTH - 1),
			f_from_float(env.game.player.my_entity.physic.height
				+ env.game.player.my_entity.physic.pos.z),
		},
		env.current_buffer, env.game.id_buf);
}

static int	manage_threads(t_thread_info infos[N_THREADS])
{
	pthread_t		tid[N_THREADS];
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	while (i < N_THREADS)
		if (pthread_create(&tid[i], NULL, &start_render, &infos[i]) != 0)
		{
			ret = 1;
			break ;
		}
		else
			++i;
	i = 0;
	while (i < N_THREADS)
		if (pthread_join(tid[i++], NULL) != 0)
		{
			ret = 1;
			++i;
		}
	return (ret);
}

void		render_multi_threaded(const t_env env, t_color *buf)
{
	t_thread_info	infos[N_THREADS];
	int				i;

	i = 0;
	while (i < N_THREADS)
	{
		infos[i] = (t_thread_info) {
			env.game, (t_context) {
				i * (WIDTH / N_THREADS),
				(i + 1) * (WIDTH / N_THREADS),
				env.game.player.my_entity.physic, -1,
				env.game.sectors[env.game.player.my_entity.physic.sector_id],
				0,
				get_ray_dir(env.game.player.my_entity.physic, 0),
				get_ray_dir(env.game.player.my_entity.physic, WIDTH - 1),
				f_from_float(env.game.player.my_entity.physic.height
					+ env.game.player.my_entity.physic.pos.z),
			}, buf, env.game.id_buf};
		i++;
	}
	if (manage_threads(infos))
	{
		console_error("Multithreading", "Can't join threads");
		exit(EXIT_FAILURE);
	}
}
