/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:01:23 by malde-ch          #+#    #+#             */
/*   Updated: 2024/12/10 06:53:18 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_nbr_row(char *map_name)
{
	int		fd; 
	int		y;	
	char	*line;

	fd = open_file(map_name);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	return (y);
}

int	get_nbr_col(char *map_name)
{
	int		x;
	int		i;
	int		fd;
	char	*line;
	char	**points;

	fd = open_file(map_name);
	line = get_next_line(fd);
	points = ft_split(line, ' ');
	x = 0;
	while (points[x] != NULL && ft_strncmp(points[x],"\n", 1))
		x++;
	i = 0;
	while (points[i] != NULL)
	{
		free(points[i]);
		i++;
	}
	free(points);
	close(fd);
	free(line);
	return (x);
}

t_matrix	*init_map(char *map_name)
{
	int			rows;
	int			cols;
	int			i;
	t_point		**map;
	t_matrix	*matrix;


	matrix = malloc(sizeof(t_matrix));

	cols = get_nbr_col(map_name);
	rows = get_nbr_row(map_name);

	map = (t_point **)malloc(sizeof(t_point *) * rows);
	if (!map)
	{
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < rows)
	{
		map[i] = (t_point *)malloc(sizeof(t_point) * cols);
		if (!map[i])
		{
			while (--i >= 0)
			{
				free(map[i]);
			}
			free(map);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	matrix->nb_col = cols;
	matrix->nb_row = rows;
	matrix->map = map;

	return (matrix);
}

void	free_matrix(t_matrix *matrix)
{
	int	x;

	if (matrix == NULL)
		return ;
	x = 0;
	while (x < matrix->nb_row)
	{
		free(matrix->map[x]);
		x++;
	}
	free(matrix->map);
	free(matrix);
}

