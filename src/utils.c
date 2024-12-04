/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:34:41 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/24 18:28:48 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void set_pixel(mlx_image_t* img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height) {
        ((uint32_t*)img->pixels)[x * img->width + y] = color;
    }
}

void	error_exit(char *message)
{

	perror(message);
	exit(EXIT_FAILURE);
}

int open_file(char *map_name)
{
    int fd;

    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        error_exit(map_name);
    return(fd);
}
