/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:31 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 00:33:14 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <limits.h>

# define WIDTH 1700
# define HEIGHT 1350

# define COS_30 0.86602540378
# define SIN_30 0.5

typedef struct s_extremes
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_extremes;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	proj_x;
	int	proj_y;
	int	color;
}	t_point;

typedef struct s_matrix
{
	int			nb_col;
	int			nb_line;
	int			zoom;
	t_point		**map;
	t_extremes	extremes;
}	t_matrix;

typedef struct s_display
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_matrix	*matrix;
}				t_display;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x0;
	int	y0;
}	t_bresenham;

void		set_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		error_exit(char *message);
int			open_file(char *map_name);

t_matrix	*extract_points_map(char *map_name);

t_matrix	*init_map(char *map_name);
void		free_matrix(t_matrix *matrix);

void		draw_bresenham_line(t_point p0, t_point p1, mlx_image_t *img);

void		iterate_matrix(t_matrix *matrix, mlx_image_t *img, \
			void (*f)(t_matrix *, mlx_image_t *, int, int));

void		connect_point(t_matrix *matrix, mlx_image_t *img, int x, int y);
void		ft_isometric(t_matrix *matrix, mlx_image_t *img, int x, int y);
void		multiplier_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y);

t_extremes	find_matrix_extremes(t_matrix *matrix);
void		add_extrem_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y);
uint32_t	get_gradient(uint32_t color1, uint32_t color2, float ratio);
void		free_split(char **lines);
void		free_display(t_display *display);
int			calculate_zoom_with_image(t_matrix *matrix);

#endif
