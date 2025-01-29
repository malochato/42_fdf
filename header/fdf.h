/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:31 by malde-ch          #+#    #+#             */
/*   Updated: 2025/01/29 00:39:26 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include <stdio.h>
#include "MLX42/MLX42.h"
#include <math.h>


#define WIDTH 1600
#define HEIGHT 1300



#define COS_30 0.86602540378 // cos(30°)
#define SIN_30 0.5           // sin(30°)


typedef struct s_extremes
{
    int min_x;
    int max_x;
    int min_y;
    int max_y;
}   t_extremes;




typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
    int proj_x;
    int	proj_y;
	int	color;
}	t_point;

typedef struct s_matrix
{
	int 	nb_col;
	int 	nb_row;
    int     zoom;
	t_point **map;
    t_extremes extremes;
}	t_matrix;

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

void set_pixel(mlx_image_t* img, int x, int y, uint32_t color);
void    error_exit(char *message);
int		open_file(char *map_name);


t_matrix *extract_points_map(char *map_name);


t_matrix *init_map(char *map_name);
void free_matrix(t_matrix *matrix);


void    draw_bresenham_line(t_point p0 , t_point p1, mlx_image_t *img);


void    print_map(t_matrix *matrix);


void iterate_matrix(t_matrix *matrix, mlx_image_t *img, void (*f)(t_matrix *, mlx_image_t *, int, int));

void place_point(t_matrix *matrix, mlx_image_t *img, int x, int y);
void connect_point(t_matrix *matrix, mlx_image_t *img, int x, int y);
void ft_isometric(t_matrix *matrix, mlx_image_t *img, int x, int y);
void ft_top(t_matrix *matrix, mlx_image_t *img, int x, int y);
void multiplier_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y);



t_extremes find_matrix_extremes(t_matrix *matrix);
void add_extrem_matrix(t_matrix *matrix, mlx_image_t *img, int x, int y);


uint32_t	get_color(t_point p0, t_point p1, t_point current);


#endif
