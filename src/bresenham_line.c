/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:07:22 by malde-ch          #+#    #+#             */
/*   Updated: 2025/01/29 02:05:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init(t_bresenham *bresenham, t_point p0, t_point p1)
{
	bresenham->x0 = p0.proj_x;
	bresenham->y0 = p0.proj_y;
	bresenham->dx = abs(p1.proj_x - p0.proj_x);
	bresenham->dy = abs(p1.proj_y - p0.proj_y);
	if (p0.proj_x < p1.proj_x)
		bresenham->sx = 1;
	else
		bresenham->sx = -1;
	if (p0.proj_y < p1.proj_y)
		bresenham->sy = 1;
	else
		bresenham->sy = -1;
}

void	draw_low_slope(t_bresenham bres, mlx_image_t *img, \
		uint32_t p0_color, uint32_t p1_color)
{
	int	i;

	i = 1;
	bres.err = 2 * bres.dy - bres.dx;
	while (i <= bres.dx + 1)
	{
		set_pixel(img, bres.x0, bres.y0, \
		get_gradient(p0_color, p1_color, (float)i / bres.dx));
		if (bres.err > 0)
		{
			bres.y0 += bres.sy;
			bres.err -= 2 * bres.dx;
		}
		bres.x0 += bres.sx;
		bres.err += 2 * bres.dy;
		i++;
	}
}

void	draw_high_slope(t_bresenham bres, mlx_image_t *img, \
		int p0_color, int p1_color)
{
	int	i;

	i = 1;
	bres.err = 2 * bres.dx - bres.dy;
	while (i <= bres.dy + 1)
	{
		set_pixel(img, bres.x0, bres.y0, \
			get_gradient(p0_color, p1_color, (float)i / bres.dy));
		if (bres.err > 0)
		{
			bres.x0 += bres.sx;
			bres.err -= 2 * bres.dy;
		}
		bres.y0 += bres.sy;
		bres.err += 2 * bres.dx;
		i++;
	}
}

void	draw_bresenham_line(t_point p0, t_point p1, mlx_image_t *img)
{
	t_bresenham	bres;

	init(&bres, p0, p1);
	if (bres.dx > bres.dy)
		draw_low_slope(bres, img, p0.color, p1.color);
	else
		draw_high_slope(bres, img, p0.color, p1.color);
}
