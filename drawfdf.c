/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:35:59 by idkahram          #+#    #+#             */
/*   Updated: 2025/02/11 01:35:59 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include "minilibx-linux/mlx.h"

double	calculate_scale(t_data *data)
{
	double	width_distance;
	double	height_distance;

	width_distance = (750 / (data->rows * data->height));
	height_distance = (450 / (data->cols * data->height));
	if (width_distance > height_distance)
		return (height_distance);
	else
		return (width_distance);
}

void	iso_projection(int *x, int *y, int z, t_data *data)
{
	double	scale;
	int		prev_x;
	int		prev_y;

	scale = calculate_scale(data);
	prev_x = *x * data->height;
	prev_y = *y * data->height;
	*x = ((prev_x - prev_y) * cos(0.5236) * scale) + 750;
	*y = ((prev_x + prev_y) * sin(0.5236) * scale) + 200 - (z * scale);
}

void	draw_horizontal_lines(int y, t_data *data, int **map)
{
	int	x;
	int	x_proj;
	int	y_proj;

	x = 0;
	while (x < data->cols - 1)
	{
		x_proj = x;
		y_proj = y;
		iso_projection(&x_proj, &y_proj, map[y][x], data);
		data->x1 = (x + 1);
		data->y1 = y;
		iso_projection(&data->x1, &data->y1, map[y][x + 1], data);
		draw_line(x_proj, y_proj, data, data->color[y][x + 1]);
		x++;
	}
}

void	draw_vertical_lines(int y, t_data *data, int **map)
{
	int	x;
	int	x_proj;
	int	y_proj;

	x = 0;
	while (x < data->cols)
	{
		x_proj = x;
		y_proj = y;
		iso_projection(&x_proj, &y_proj, map[y][x], data);
		if (y < data->rows - 1)
		{
			data->x1 = x;
			data->y1 = (y + 1);
			iso_projection(&data->x1, &data->y1, map[y + 1][x], data);
			draw_line(x_proj, y_proj, data, data->color[y + 1][x]);
		}
		x++;
	}
}

void	draw_map(int **map, t_data *data)
{
	int	y;

	y = 0;
	while (y < data->rows)
	{
		draw_horizontal_lines(y, data, map);
		draw_vertical_lines(y, data, map);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}
