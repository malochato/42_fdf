/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:34:48 by malde-ch          #+#    #+#             */
/*   Updated: 2025/01/29 02:24:32 by malde-ch         ###   ########.fr       */
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



void	free_split(char **lines)
{
	int	i; 

	i = 0;
	while (lines[i] != NULL)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
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
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;
    color = (0xFF << 24) | (blue << 16) | (green << 8) | red;
    free_split(colors);
    return (color);
}


void	populate_map(t_matrix *matrix, char **lines)
{
	char	**row;
	int		x;
	int		y;

	y = 0;
	while (y < matrix->nb_row)
	{
		x = 0;
		row = ft_split(lines[y], ' ');
		while (row[x])
		{
			matrix->map[y][x].x = x;
			matrix->map[y][x].y = y;
			matrix->map[y][x].z = ft_atoi(row[x]);
			matrix->map[y][x].color = extract_color(row[x]);
			x++;
		}
		if (x != matrix->nb_col)
		{
			ft_printf("Number of colum is not always the same\n");
			exit(EXIT_FAILURE);
		}	// a mieux faire et expliquer que la map est pas bonne
		free_split(row);
		y++;
	}
}

void	print_map(t_matrix *matrix)
{
	int	x;
	int	y;

	x = 0;
	while (x < matrix->nb_row)
	{
		y = 0;
		while (y < matrix->nb_col)
		{
			printf("%x ", matrix->map[x][y].color);	
			y++;
		}
		printf("\n");
		x++;
	}
	printf("\n");
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


