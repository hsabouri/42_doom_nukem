/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_mini_sec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:25:50 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/13 15:25:51 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static void				self_render(const t_component self, t_color *buf)
{
	const t_mini_weapon		mini = *(t_mini_weapon *)self.state;
	const t_weapons_state	parent_state = *(t_weapons_state *)mini.parent;
	const uint32_t			equiped = parent_state.player->secondary;
	const t_img				sprite = **(t_img **)anth(
		&parent_state.weapons[equiped].sprite, 0);

	background(buf, NO_COLOR, self.size);
	if (parent_state.weapons[equiped].ammo == 0)
	{
		SDL_RenderCopy(parent_state.sdl->renderer, mini.str.text_texture, NULL,
			&((SDL_Rect){mini.str.x + self.pos.x,
				mini.str.y + self.pos.y, mini.str.w,
				mini.str.h}));
	}
	component_image(sprite, (t_pix) {150, HEIGHT - sprite.height - 10},
		self.size, buf);
}

static int				self_update(t_component *self, void *parent_state)
{
	const t_weapons_state	*weapon = (t_weapons_state *)parent_state;
	t_mini_weapon			*mini_state;
	char					*str;
	char					*tmp;

	mini_state = (t_mini_weapon *)self->state;
	if (mini_state->last_ammo != weapon->weapons[weapon->last_secondary].ammo)
	{
		str = ft_strdup(ft_itoa(weapon->weapons[weapon->last_secondary].ammo));
		tmp = str;
		str = ft_strjoin(str, "/");
		ft_strdel(&tmp);
		tmp = str;
		str = ft_strjoin(str, ft_itoa(weapon->weapons
			[weapon->last_secondary].ammo_max));
		ft_strdel(&tmp);
		self->text = component_text(str, (t_pix) {self->img.width * 3 + 15,
		HEIGHT - self->img.height + 15}, weapon->sdl);
		ft_strdel(&str);
		mini_state->last_ammo = weapon->weapons[weapon->last_secondary].ammo;
		return (1);
	}
	else if (mini_state->last_ammo == 0)
		return (1);
	return (0);
}

static t_mini_weapon	*init_state(void *parent_state)
{
	t_weapons_state	*weapons;
	t_mini_weapon	*mini_state;

	weapons = (t_weapons_state *)parent_state;
	mini_state = (t_mini_weapon *)safe_malloc(sizeof(t_mini_weapon),
		"components");
	mini_state->parent = parent_state;
	mini_state->last_ammo = weapons->weapons[weapons->last_secondary].ammo;
	mini_state->str = component_text("No munition", (t_pix) {WIDTH / 2 - 48,
			HEIGHT / 2 - 40}, weapons->sdl);
	return (mini_state);
}

t_array					mini_weapon_s(t_array array, void *parent_state,
t_sdl *sdl)
{
	t_component		component;
	t_img			**sprite;
	t_weapons_state	*weapon_state;
	char			*str;
	char			*tmp;

	weapon_state = (t_weapons_state *)parent_state;
	sprite = anth(&weapon_state->weapons[weapon_state->last_secondary].sprite,
		0);
	component.display = 1;
	component.img = **sprite;
	component.size.x = WIDTH;
	component.size.y = HEIGHT;
	component.pos.x = 0;
	component.pos.y = 0;
	str = ft_strdup(ft_itoa(weapon_state->weapons
		[weapon_state->last_secondary].ammo));
	tmp = str;
	str = ft_strjoin(str, "/");
	ft_strdel(&tmp);
	tmp = str;
	str = ft_strjoin(str, ft_itoa(weapon_state->weapons
		[weapon_state->last_secondary].ammo_max));
	ft_strdel(&tmp);
	component.text = component_text(str, (t_pix) {component.img.width * 3 + 15,
		HEIGHT - component.img.height + 15}, sdl);
	ft_strdel(&str);
	component.state = init_state(parent_state);
	component.update = &self_update;
	component.destroy = &no_destroy;
	component.render = &self_render;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.complete_render = NULL;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}
