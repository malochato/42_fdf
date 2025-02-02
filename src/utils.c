/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:34:41 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/01 00:14:57 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	pixel_index;
	int	bpp;

	bpp = sizeof(int32_t);
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
	{
		pixel_index = (y * img->width + x) * bpp;
		ft_memcpy(&img->pixels[pixel_index], &color, bpp);
	}
}

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	open_file(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		error_exit(map_name);
	return (fd);
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

void	free_display(t_display *display)
{
	if (display)
	{
		if (display->mlx)
			mlx_terminate(display->mlx);
		free(display);
	}
}
