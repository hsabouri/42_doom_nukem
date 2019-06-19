/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:42:52 by hugo              #+#    #+#             */
/*   Updated: 2019/05/31 14:21:22 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H
# include <libft.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>

# define ID_LENGTH 0
# define IS_COLOR_MAP 1
# define IMAGE_TYPE 2
# define BPP 16
# define T_WIDTH 6
# define T_HEIGHT 7

typedef struct		s_color
{
	u_int8_t		r;
	u_int8_t		g;
	u_int8_t		b;
	u_int8_t		a;
}					t_color;

typedef struct		s_img
{
	unsigned int	width;
	unsigned int	height;
	t_color			*content;
	unsigned int	edit;
}					t_img;

t_img				parse_tga(const char *path, unsigned int edit);

#endif
