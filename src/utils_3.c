/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_extremes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:44:55 by malde-ch          #+#    #+#             */
/*   Updated: 2024/12/03 09:30:00 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf.h"
#include <limits.h>

t_extremes init_extremes(void)
{
    t_extremes extremes;

    extremes.min_x = INT_MAX;
    extremes.max_x = INT_MIN;
    extremes.min_y = INT_MAX;
    extremes.max_y = INT_MIN;

    return extremes;
}

void update_extremes(t_extremes *extremes, t_point point)
{
    if (point.proj_x < extremes->min_x)
        extremes->min_x = point.proj_x;
    if (point.proj_x > extremes->max_x)
        extremes->max_x = point.proj_x;

    if (point.proj_y < extremes->min_y)
        extremes->min_y = point.proj_y;
    if (point.proj_y > extremes->max_y)
        extremes->max_y = point.proj_y;
}

t_extremes find_matrix_extremes(t_matrix *matrix)
{
    int x;
    int y;
    t_extremes extremes;
    
    extremes = init_extremes();

    x = 0;
    while(x < matrix->nb_row)
    {
        y = 0;
        while(y < matrix->nb_col)
        {
            update_extremes(&extremes, matrix->map[x][y]);
            y++;
        }
        x++;
    }
    return extremes;
}

