/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:05:51 by malde-ch          #+#    #+#             */
/*   Updated: 2024/12/14 05:53:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_extremes(t_extremes extremes)
{
	printf("Min X: %d, Max X: %d\n", extremes.min_x, extremes.max_x);
	printf("Min Y: %d, Max Y: %d\n", extremes.min_y, extremes.max_y);
}

int	calculate_zoom_with_image(t_matrix *matrix)
{
	int	cell_width;
	int	cell_height;

	cell_width = WIDTH / matrix->nb_col / 2;
	cell_height = HEIGHT / matrix->nb_row / 2;
	printf("1 = %d, 2 = %d\n", cell_width, cell_height);
	if (cell_height <= cell_width)
		return (cell_height);
	else
		return (cell_width);
}

void	create_img(t_matrix *matrix, mlx_image_t *img)
{
	t_extremes	extremes;

	matrix->zoom = calculate_zoom_with_image(matrix);

	iterate_matrix(matrix, NULL, multiplier_matrix);
	iterate_matrix(matrix, img, ft_isometric);

	extremes = find_matrix_extremes(matrix);
	matrix->extremes = extremes;
	iterate_matrix(matrix, img, add_extrem_matrix);

	iterate_matrix(matrix, img, connect_point);
}

void my_loop_function(void *param)
{
	(void)param;	
	printf("loop\n");
}

void handle_key(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx;
	mlx = (mlx_t *)param;
    //printf("Key pressed: %d\n", keydata.key);
    if (keydata.key == MLX_KEY_ESCAPE)
	{
        exit(0);
	}
	if (keydata.key == MLX_KEY_D)
	{
		printf("D\n");
	}
	if (keydata.key == MLX_KEY_A)
		printf("A\n");
}


int	create_display_windows(t_matrix *matrix)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, " 🇪🇸 FDF 🇫🇷", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	(void)matrix;

	img = mlx_new_image(mlx, HEIGHT, WIDTH);

	create_img(matrix, img);

	if(!img ||(mlx_image_to_window(mlx, img, 0, 0 ) < 0))
		exit(EXIT_FAILURE);

	//print_map(matrix);

	//mlx_delete_image(mlx, img);

	mlx_put_string(mlx,"FDF",10, 10);

	mlx_key_hook(mlx, handle_key, img);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}


int	main(int argc, char **argv)
{
	t_matrix	*matrix;

	if (argc != 2)
		return (1);
	matrix = extract_points_map(argv[1]);

	create_display_windows(matrix);


		
	free_matrix(matrix);
	return (0);
}


