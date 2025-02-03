/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:51:17 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 00:29:27 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iterate_matrix(t_matrix *matrix, mlx_image_t *img, \
	void (*f)(t_matrix *, mlx_image_t *, int, int))
{
	int	x;
	int	y;

	x = 0;
	while (x < matrix->nb_col)
	{
		y = 0;
		while (y < matrix->nb_line)
		{
			f(matrix, img, x, y);
			y++;
		}
		x++;
	}
}

void	multiplier_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	matrix->map[x][y].x *= matrix->zoom;
	matrix->map[x][y].y *= matrix->zoom;
	matrix->map[x][y].z *= matrix->zoom;
	(void)img;
}

void	connect_point(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	if (x + 1 < matrix->nb_col)
		draw_bresenham_line(matrix->map[x][y], matrix->map[x + 1][y], img);
	if (y + 1 < matrix->nb_line)
		draw_bresenham_line(matrix->map[x][y], matrix->map[x][y + 1], img);
}

void	ft_isometric(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	int		temp_x;
	int		temp_y;
	int		temp_z;

	temp_x = matrix->map[x][y].x;
	temp_y = matrix->map[x][y].y;
	temp_z = matrix->map[x][y].z;
	matrix->map[x][y].proj_x = (temp_y + temp_x) * COS_30;
	matrix->map[x][y].proj_y = (temp_y - temp_x) * SIN_30 - temp_z;
	(void)img;
}

void	add_extrem_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	if (matrix->extremes.min_x < 0)
		matrix->map[x][y].proj_x += abs(matrix->extremes.min_x);
	if (matrix->extremes.min_y < 0)
		matrix->map[x][y].proj_y += abs(matrix->extremes.min_y);
	(void)img;
}
