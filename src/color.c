/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:17:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/01/29 00:34:21 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	get_color(t_point p0, t_point p1, t_point current)
{
	int		delta_x;
	int		delta_y;
	int		delta_z;
	int		current_z;
	int		red;
	int		green;
	int		blue;

	delta_x = p1.x - p0.x;
	delta_y = p1.y - p0.y;
	delta_z = p1.z - p0.z;
	current_z = current.z - p0.z;
	red = p0.color >> 16;
	green = (p0.color >> 8) & 0xFF;
	blue = p0.color & 0xFF;
	if (delta_x != 0)
		red += (p1.color >> 16) - red * current_z / delta_z;
	if (delta_y != 0)
		green += ((p1.color >> 8) & 0xFF) - green * current_z / delta_z;
	if (delta_z != 0)
		blue += (p1.color & 0xFF) - blue * current_z / delta_z;
	return ((red << 16) + (green << 8) + blue);
}