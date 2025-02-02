/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:00:10 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 18:00:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	get_red(uint32_t color)
{
	return ((color >> 16) & 0xFF);
}

static unsigned char	get_green(uint32_t color)
{
	return ((color >> 8) & 0xFF);
}

static unsigned char	get_blue(uint32_t color)
{
	return ((color) & 0xFF);
}

uint32_t	get_gradient(uint32_t color1, uint32_t color2, float ratio)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)(get_red(color1) + ratio \
		* (get_red(color2) - get_red(color1)));
	g = (unsigned char)(get_green(color1) + ratio \
		* (get_green(color2) - get_green(color1)));
	b = (unsigned char)(get_blue(color1) + ratio \
		* (get_blue(color2) - get_blue(color1)));
	return ((0xFF << 24) | (r << 16) | (g << 8) | b);
}
