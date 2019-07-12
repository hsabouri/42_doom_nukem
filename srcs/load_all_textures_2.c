/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_textures_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:19:13 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 12:30:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_img	*load_all_textures_6(t_img *textures)
{
	textures[116] = parse_tga("./textures/environment/stairs_down.tga", 1);
	textures[117] = parse_tga("./textures/environment/stairs_up_down.tga", 1);
	textures[118] = parse_tga("./textures/environment/wc.tga", 1);
	textures[119] = parse_tga("./textures/environment/elevator.tga", 1);
	textures[120] = parse_tga("./textures/environment/plexi.tga", 1);
	textures[121] = parse_tga("./textures/environment/ccc_logo.tga", 1);
	textures[122] = parse_tga("./textures/environment/plexi_desk.tga", 1);
	textures[123] = parse_tga("./textures/environment/plexi_desk_2.tga", 1);
	textures[124] = parse_tga("./textures/environment/plexi_desk_3.tga", 1);
	textures[125] = parse_tga("./textures/environment/hsabouri_pic.tga", 1);
	textures[126] = parse_tga("./textures/environment/fmerding_pic.tga", 1);
	textures[127] = parse_tga("./textures/environment/lbougero_pic.tga", 1);
	textures[128] = parse_tga("./textures/environment/iporsenn_pic.tga", 1);
	textures[129] = parse_tga("./textures/environment/nope_grumpy_2.tga", 1);
	textures[130] = parse_tga("./textures/items/wc_1.tga", 1);
	textures[131] = parse_tga("./textures/items/wc_2.tga", 1);
	textures[132] = parse_tga("./textures/items/wc_3.tga", 1);
	return (textures);
}
