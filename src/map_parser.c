/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:34:48 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/24 18:56:06 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char **get_all_line(int fd)
{
	char *line;
	char *file;
	char *tmp;
	char **lines;
	
	file = ft_strdup("");
	line = get_next_line(fd);
	while(line)
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

void free_split(char **lines)
{
	int i; 

	i = 0;
	while(lines[i] != NULL)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void populate_map(t_matrix *matrix, char **lines)
{
	int x;
	int y;
	char **row;

	y = 0;
	while(y < matrix->nb_row)
	{
		x = 0;
		row = ft_split(lines[y], ' ');
		//while(y < matrix->nb_col)
		while(row[x])
		{
			matrix->map[y][x].x = x;
			matrix->map[y][x].y = y;
			matrix->map[y][x].z = ft_atoi(row[x]);
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

void print_map(t_matrix *matrix)
{
    int	x;
	int	y;

	x = 0;
	while(x < matrix->nb_row)
	{
		y = 0;
        while(y < matrix->nb_col)
		{
			printf("%d ", matrix->map[x][y].z);	
			y++;
		}
		printf("\n");
		x++;
    }
	printf("\n");
}

t_matrix *extract_points_map(char *map_name)
{
	t_matrix *matrix;
	int fd;
	char **lines;

	
	fd = open_file(map_name);
	lines = get_all_line(fd);

	matrix = init_map(map_name);
	//printf("col = %d, row = %d\n", matrix->nb_col, matrix->nb_row);

	populate_map(matrix, lines);

	
	close(fd);
	free_split(lines);
	return(matrix);
}

