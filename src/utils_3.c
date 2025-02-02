/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:14:40 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 18:14:44 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_extremes	init_extremes(void)
{
	t_extremes	extremes;

	extremes.min_x = INT_MAX;
	extremes.max_x = INT_MIN;
	extremes.min_y = INT_MAX;
	extremes.max_y = INT_MIN;
	return (extremes);
}

void	update_extremes(t_extremes *extremes, t_point point)
{
	if (point.proj_x < extremes->min_x)
		extremes->min_x = point.proj_x;
	if (point.proj_x > extremes->max_x)
		extremes->max_x = point.proj_x;
	if (point.proj_y < extremes->min_y)
		extremes->min_y = point.proj_y;
	if (point.proj_y > extremes->max_y)
		extremes->max_y = point.proj_y;
}

t_extremes	find_matrix_extremes(t_matrix *matrix)
{
	int			x;
	int			y;
	t_extremes	extremes;

	extremes = init_extremes();
	x = 0;
	while (x < matrix->nb_col)
	{
		y = 0;
		while (y < matrix->nb_line)
		{
			update_extremes(&extremes, matrix->map[x][y]);
			y++;
		}
		x++;
	}
	return (extremes);
}

int	calculate_z_range(t_matrix *matrix)
{
	int	z_min;
	int	z_max;
	int	z_value;
	int	i;
	int	j;

	z_min = INT_MAX;
	z_max = INT_MIN;
	i = 0;
	while (i < matrix->nb_col)
	{
		j = 0;
		while (j < matrix->nb_line)
		{
			z_value = matrix->map[i][j].z;
			if (z_value < z_min)
				z_min = z_value;
			if (z_value > z_max)
				z_max = z_value;
			j++;
		}
		i++;
	}
	return (z_max - z_min);
}

int	calculate_zoom_with_image(t_matrix *matrix)
{
	int	cell_width;
	int	cell_height;
	int	z_range;
	int	zoom_factor;

	z_range = calculate_z_range(matrix);
	cell_width = WIDTH / matrix->nb_col;
	cell_height = HEIGHT / (matrix->nb_line + z_range);
	if (cell_width < cell_height)
		zoom_factor = cell_width;
	else
		zoom_factor = cell_height;
	if (matrix->nb_line > 100 || matrix->nb_col > 100)
		zoom_factor *= 1.5;
	if (z_range < 20)
		zoom_factor *= 0.8;
	return (zoom_factor);
}
