/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:51:17 by malde-ch          #+#    #+#             */
/*   Updated: 2024/12/10 07:05:44 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void	iterate_matrix(t_matrix *matrix, mlx_image_t *img, \
	void (*f)(t_matrix *, mlx_image_t *, int, int))
{
	int	x;
	int	y;

	x = 0;
	while (x < matrix->nb_row)
	{
		y = 0;
		while (y < matrix->nb_col)
		{
			f(matrix, img, x, y);
			y++;
		}
		x++;
	}
	ft_printf("max y = %d et nb_col = %d\n",y, matrix->nb_col);
	ft_printf("max x = %d et nb_row = %d\n",x, matrix->nb_row);

}

void	multiplier_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	matrix->map[x][y].x *= matrix->zoom;
	matrix->map[x][y].y *= matrix->zoom;
	matrix->map[x][y].z *= matrix->zoom;
	(void)img;

}

void	place_point(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	set_pixel(img, matrix->map[x][y].proj_x, matrix->map[x][y].proj_y, 0xFFFFFFFF);
}

void	connect_point(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	if (x + 1 < matrix->nb_row)
		draw_bresenham_line(matrix->map[x][y], matrix->map[x + 1][y], img);
	if (y + 1 < matrix->nb_col)
		draw_bresenham_line(matrix->map[x][y + 1], matrix->map[x][y], img);
}



void	ft_isometric(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	int	temp_x = matrix->map[x][y].x;
	int	temp_y = matrix->map[x][y].y;
	int	temp_z = matrix->map[x][y].z;

	double angle = 3.141592 / 6; // 30 degrés
	int offset_x = 0;      // Décalage horizontal
	int offset_y = 0;      // Décalage vertical

	// matrix->map[x][y].proj_y = (temp_x - temp_y) * cos(angle) + offset_x;
	// matrix->map[x][y].proj_x = (temp_x + temp_y) * sin(angle) - temp_z + offset_y;

	matrix->map[x][y].proj_x = (temp_y - temp_x) * sin(angle) - temp_z + offset_y;
	matrix->map[x][y].proj_y = (temp_x + temp_y) * cos(angle) + offset_x;

	//matrix->map[x][y].proj_y = (temp_x - temp_y) * COS_30 + offset_x;
	//matrix->map[x][y].proj_x = (temp_x + temp_y) * SIN_30 - temp_z + offset_y;

	(void)img;
}


void	ft_top(t_matrix *matrix, mlx_image_t *img, int x, int y)
{
	matrix->map[x][y].proj_y = matrix->map[x][y].y;
	matrix->map[x][y].proj_x = matrix->map[x][y].x;
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


