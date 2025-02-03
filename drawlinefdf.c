#include "fdf.h"

void	set_direction(int x0, int x1, int y0, int y1, int *sx, int *sy)
{
	*sx = (x0 < x1) ? 1 : -1;
	*sy = (y0 < y1) ? 1 : -1;
}

void draw_pixel(int x, int y, t_data *data, unsigned int color)
{
	if (x >= 0 && x < 1500 && y >= 0 && y < 900)
    {
	int pixel_index = (y * data->len) + (x * (data->bitt / 8));
	*(unsigned int *)(data->narr + pixel_index) = color;
	}
}

void update_position(int *x, int *y, int *err, int dx, int dy, int sx, int sy)
{
	int e2 = 2 * (*err);

	if (e2 > -dy)
	{
		*err -= dy;
		*x += sx;
	}
	if (e2 < dx)
	{
		*err += dx;
		*y += sy;
	}
}

void draw_line(int x0, int y0, int x1, int y1, t_data *data, unsigned int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx, sy;
	int err = dx - dy;

	set_direction(x0, x1, y0, y1, &sx, &sy);

	while (1)
	{
		draw_pixel(x0, y0, data, color);

		if (x0 == x1 && y0 == y1)
			break;

		update_position(&x0, &y0, &err, dx, dy, sx, sy);
	}
}
