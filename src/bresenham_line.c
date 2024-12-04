/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:07:22 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/24 17:27:49 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void init(t_bresenham *bresenham, t_point p0, t_point p1)
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


void draw_low_slope(t_bresenham bres, mlx_image_t *img, int color) {
    int i = 0;
    bres.err = 2 * bres.dy - bres.dx;

    while (i <= bres.dx) {
        set_pixel(img, bres.x0, bres.y0, color);

        if (bres.err > 0) {
            bres.y0 += bres.sy;
            bres.err -= 2 * bres.dx;
        }
        bres.x0 += bres.sx;
        bres.err += 2 * bres.dy;
        i++;
    }
}

void draw_high_slope(t_bresenham bres, mlx_image_t *img, int color) {
    int i = 0;
    bres.err = 2 * bres.dx - bres.dy;

    while (i <= bres.dy) {
        set_pixel(img, bres.x0, bres.y0, color);

        if (bres.err > 0) {
            bres.x0 += bres.sx;
            bres.err -= 2 * bres.dy;
        }
        bres.y0 += bres.sy;
        bres.err += 2 * bres.dx;
        i++;
    }
}

void draw_bresenham_line(t_point p0, t_point p1, mlx_image_t *img) {
    t_bresenham bres;

    init(&bres, p0, p1);

    if (bres.dx > bres.dy) {
        draw_low_slope(bres, img, 0xFFFFFFFF);
    } else {
        draw_high_slope(bres, img, 0xFFFFFFFF);
    }
}
