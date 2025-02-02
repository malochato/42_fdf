/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:34:48 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 00:19:05 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_all_line(int fd)
{
	char	*line;
	char	*file;
	char	*tmp;
	char	**lines;

	file = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(file, line);
		free(file);
		file = ft_strdup(tmp);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	lines = ft_split(file, '\n');
	free(file);
	return (lines);
}

int	extract_color(char *str)
{
	char	**colors;
	int		color;
	int		red;
	int		green;
	int		blue;

	colors = ft_split(str, ',');
	if (colors[1] == NULL)
	{
		free_split(colors);
		return (0xFFFFFFFF);
	}
	color = ft_atoi_base(colors[1] + 2, 16);
	blue = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	red = color & 0xFF;
	color = (0xFF << 24) | (red << 16) | (green << 8) | blue;
	free_split(colors);
	return (color);
}

void	handle_invalid_col(t_matrix *matrix, char **row, char **lines, int x)
{
	ft_putstr_fd("Number of columns is not always the same\n", 2);
	free_split(row);
	free_split(lines);
	while (x >= 0)
	{
		free(matrix->map[x]);
		x--;
	}
	free(matrix->map);
	free(matrix);
	exit(EXIT_FAILURE);
}

void	populate_map(t_matrix *matrix, char **lines)
{
	char	**row;
	int		x;
	int		y;

	y = 0;
	while (y < matrix->nb_line)
	{
		x = 0;
		row = ft_split(lines[y], ' ');
		while (row[x])
		{
			matrix->map[x][y].x = x;
			matrix->map[x][y].y = y;
			matrix->map[x][y].z = ft_atoi(row[x]);
			matrix->map[x][y].color = extract_color(row[x]);
			x++;
		}
		if (x != matrix->nb_col)
			handle_invalid_col(matrix, row, lines, x);
		free_split(row);
		y++;
	}
}

t_matrix	*extract_points_map(char *map_name)
{
	t_matrix	*matrix;
	int			fd;
	char		**lines;

	fd = open_file(map_name);
	lines = get_all_line(fd);
	matrix = init_map(map_name);
	populate_map(matrix, lines);
	close(fd);
	free_split(lines);
	return (matrix);
}
