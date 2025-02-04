#include "fdf.h"

void	handle_movement(int keycode, t_data *data)
{
	if (keycode == 65362)
		data->offsety -= 20;
	else if (keycode == 65364)
		data->offsety += 20;
	else if (keycode == 65363)
		data->offsetx += 20;
	else if (keycode == 65361)
		data->offsetx -= 20;
}

void	handle_scale(int keycode, t_data *data)
{
	if (keycode == 119)
		data->scale += 0.1;
	else if (keycode == 115)
	{
		if (data->scale > 0)
			data->scale -= 0.1;
	}
}

void	handle_zoom(int keycode, t_data *data)
{
	if (keycode == 113)
	{
		data->zoom += 1;
		data->scale = calculate_scale(data);
	}
	else if (keycode == 101)
	{
		if (data->zoom > 1)
		{
			data->zoom -= 1;
			data->scale = calculate_scale(data);
		}
	}
}

int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		handle_esc_key(data);
	else
	{
		handle_movement(keycode, data);
		handle_scale(keycode, data);
		handle_zoom(keycode, data);
		mlx_destroy_image(data->mlx, data->image);
		data->image = mlx_new_image(data->mlx, 1500, 900);
		draw_map(data->map, data);
	}
	return (0);
}
