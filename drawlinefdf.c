/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawlinefdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:36:07 by idkahram          #+#    #+#             */
/*   Updated: 2025/02/11 01:36:07 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	draw_pixel(int x, int y, t_data *data, unsigned int color)
{
	int	pixel_index;

	if (x >= 0 && x < 1500 && y >= 0 && y < 900)
	{
		pixel_index = (y * data->len) + (x * (data->bitt / 8));
		*(unsigned int *)(data->narr + pixel_index) = color;
	}
}

void	update_position(int *x, int *y, int *err, t_data *data)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -data->dy)
	{
		*err -= data->dy;
		*x += data->sx;
	}
	if (e2 < data->dx)
	{
		*err += data->dx;
		*y += data->sy;
	}
}

void	draw_line(int x0, int y0, t_data *data, unsigned int color)
{
	int	err;

	data->dx = abs(data->x1 - x0);
	data->dy = abs(data->y1 - y0);
	err = data->dx - data->dy;
	if (x0 < data->x1)
		data->sx = 1;
	else
		data->sx = -1;
	if (y0 < data->y1)
		data->sy = 1;
	else
		data->sy = -1;
	while (1)
	{
		draw_pixel(x0, y0, data, color);
		if (x0 == data->x1 && y0 == data->y1)
			break ;
		update_position(&x0, &y0, &err, data);
	}
}
