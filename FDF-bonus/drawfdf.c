#include "fdf.h"

double	calculate_scale(t_data *data)
{
	double	width_distance;
	double	height_distance;

	width_distance = (double)(1600) / (data->rows * data->zoom);
	height_distance = (double)(550) / (data->cols * data->zoom);
	if (width_distance > height_distance)
		return (height_distance);
	else
		return (width_distance);
}

void	iso_projection(int *x, int *y, int z, t_data *data)
{
	double	scl;
	int		prev_x;
	int		prev_y;

	prev_x = *x;
	prev_y = *y;
	scl = data->scale;
	*x = (prev_x - prev_y) * cos(0.6) * scl + data->offsetx;
	*y = (prev_x + prev_y) * sin(0.6) * scl + data->offsety - (z * scl);
}

void	draw_horizontal_lines(int y, t_data *data, int **map)
{
	int	x;
	int	x_proj;
	int	y_proj;
	int	x_next;
	int	y_next;

	x = 0;
	while (x < data->cols - 1)
	{
		x_proj = x * data->zoom;
		y_proj = y * data->zoom;
		iso_projection(&x_proj, &y_proj, map[y][x], data);
		x_next = (x + 1) * data->zoom;
		y_next = y * data->zoom;
		iso_projection(&x_next, &y_next, map[y][x + 1], data);
		draw_line(x_proj, y_proj, x_next, y_next, data, data->color[y][x + 1]);
		x++;
	}
}

void	draw_vertical_lines(int y, t_data *data, int **map)
{
	int	x;
	int	x_prj;
	int	y_prj;
	int	x_nxt;
	int	y_nxt;

	x = 0;
	while (x < data->cols)
	{
		x_prj = x * data->zoom;
		y_prj = y * data->zoom;
		iso_projection(&x_prj, &y_prj, map[y][x], data);
		if (y < data->rows - 1)
		{
			x_nxt = x * data->zoom;
			y_nxt = (y + 1) * data->zoom;
			iso_projection(&x_nxt, &y_nxt, map[y + 1][x], data);
			draw_line(x_prj, y_prj, x_nxt, y_nxt, data, data->color[y + 1][x]);
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
