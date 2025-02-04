#include "fdf.h"

void	free_map(int **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_color(unsigned int **color)
{
	int	i;

	i = 0;
	if (color != NULL)
	{
		while (color[i])
		{
			free(color[i]);
			i++;
		}
		free(color);
	}
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_map(data->map);
	free_color(data->color);
	if (data->image != NULL)
		mlx_destroy_image(data->mlx, data->image);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	handle_esc_key(t_data *data)
{
	free_map(data->map);
	free_color(data->color);
	if (data->image != NULL)
		mlx_destroy_image(data->mlx, data->image);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	printf("ESC tuşuna basildi. Program kapaniyor.\n");
	exit(0);
}
