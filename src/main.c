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

void	print_extremes(t_extremes extremes)
{
	printf("Min X: %d, Max X: %d\n", extremes.min_x, extremes.max_x);
	printf("Min Y: %d, Max Y: %d\n", extremes.min_y, extremes.max_y);
}

/* int	calculate_zoom_with_image(t_matrix *matrix)
{
	int	cell_width;
	int	cell_height;

	cell_width = WIDTH / matrix->nb_col;   // Largeur de chaque cellule
	cell_height = HEIGHT / matrix->nb_row; // Hauteur de chaque cellule
	return (cell_width < cell_height ? cell_width : cell_height);
} */

int	calculate_zoom_with_image(t_matrix *matrix)
{
	int	cell_width;
	int	cell_height;
	int	z_range;
	int	zoom_factor;

	int z_min = INT_MAX;
	int z_max = INT_MIN;

	// Trouver z_min et z_max
	for (int i = 0; i < matrix->nb_row; i++)
	{
		for (int j = 0; j < matrix->nb_col; j++)
		{
			int z_value = matrix->map[i][j].z;
			if (z_value < z_min) z_min = z_value;
			if (z_value > z_max) z_max = z_value;
		}
	}

	z_range = z_max - z_min;  // Différence entre le plus haut et le plus bas point

	cell_width = WIDTH / matrix->nb_col;   // Largeur par cellule
	cell_height = HEIGHT / (matrix->nb_row + z_range); // Hauteur ajustée avec la profondeur Z

	// On prend le plus petit pour éviter les débordements
	zoom_factor = (cell_width < cell_height) ? cell_width : cell_height;

	return zoom_factor;
}



void	create_img(t_matrix *matrix, mlx_image_t *img)
{
	t_extremes	extremes;

	matrix->zoom = calculate_zoom_with_image(matrix);
	printf("Zoom: %d\n", matrix->zoom);

	iterate_matrix(matrix, NULL, multiplier_matrix);
	iterate_matrix(matrix, img, ft_isometric);

	extremes = find_matrix_extremes(matrix);
	matrix->extremes = extremes;
	print_extremes(extremes);
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
	t_image		*image;

	image = (t_image *)param;
	(void)image;
    //printf("Key pressed: %d\n", keydata.key);
    if (keydata.key == MLX_KEY_ESCAPE)
	{
        exit(0);
	}
	if (keydata.key == MLX_KEY_D)
	{
		image->img->instances[0].x += 5;
	}
	if (keydata.key == MLX_KEY_A)
		image->img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_W)
		image->img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S)
		image->img->instances[0].y += 5;

}

int	create_display_windows(t_matrix *matrix)
{
	//mlx_t		*mlx;
	//mlx_image_t	*img;
	t_image		*image;

	image = malloc(sizeof(t_image));
	if (!image)
		exit(EXIT_FAILURE);
	

	image->mlx = mlx_init(WIDTH, HEIGHT, " 🇪🇸 FDF 🇫🇷", false);
	if (!image->mlx)
		exit(EXIT_FAILURE);
	(void)matrix;

	image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	if (!image->img)
		exit(EXIT_FAILURE);
	create_img(matrix, image->img);

	if(!image->img ||(mlx_image_to_window(image->mlx, image->img, 0, 0 ) < 0))
		exit(EXIT_FAILURE);

	//print_map(matrix);

	//mlx_delete_image(mlx, img);

	mlx_put_string(image->mlx,"FDF",10, 10);

	mlx_key_hook(image->mlx, handle_key, image);

	mlx_loop(image->mlx);
	mlx_terminate(image->mlx);
	free(image);
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


