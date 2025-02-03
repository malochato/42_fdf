/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:05:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 00:35:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_img(t_matrix *matrix, mlx_image_t *img)
{
	t_extremes	extremes;

	iterate_matrix(matrix, NULL, multiplier_matrix);
	iterate_matrix(matrix, img, ft_isometric);
	extremes = find_matrix_extremes(matrix);
	matrix->extremes = extremes;
	iterate_matrix(matrix, img, add_extrem_matrix);
	iterate_matrix(matrix, img, connect_point);
	if (!matrix || !img)
		return (1);
	return (0);
}

void	init_display(t_display *display)
{
	display->img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
	if (!display->img)
		exit(EXIT_FAILURE);
	create_img(display->matrix, display->img);
	if (!display->img || \
	(mlx_image_to_window(display->mlx, display->img, 0, 0) < 0))
		exit(EXIT_FAILURE);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(display->mlx);
	if (keydata.key == MLX_KEY_D)
		display->img->instances[0].x += 5;
	if (keydata.key == MLX_KEY_A)
		display->img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_W)
		display->img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S)
		display->img->instances[0].y += 5;
}

int	main(int argc, char **argv)
{
	t_matrix	*matrix;
	t_display	*display;

	if (argc != 2)
		return (1);
	matrix = extract_points_map(argv[1]);
	matrix->zoom = calculate_zoom_with_image(matrix);
	display = malloc(sizeof(t_display));
	if (!display)
		exit(EXIT_FAILURE);
	display->mlx = mlx_init(WIDTH, HEIGHT, " 🇪🇸 FDF 🇫🇷", false);
	if (!display->mlx)
		exit(EXIT_FAILURE);
	display->matrix = matrix;
	init_display(display);
	mlx_key_hook(display->mlx, handle_key, display);
	mlx_loop(display->mlx);
	free_display(display);
	free_matrix(matrix);
	return (0);
}
